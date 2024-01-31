#include "../../headers/chessmodel/chessmodel.h"
#include <cctype>
#include <QDebug>

ChessModel::ChessModel() {
    blackKing = {};
    whiteKing = {};
    initializePieces(this->pieces, whiteKing, blackKing);
    fontSize = 14;
    lftBrdPadding = 200;
    topBrdPadding = 150;
    cellSize = 50;
    pPawnMovesVector = {};
    currentlySelectedPawn = nullptr;
    deadPieces = {};
    isWhitePlayerTurn = true;
    isGameOn = false;
    turnNumber = 1;
    fromLastKill = 0;
}

auto ChessModel::getLftPadding() const -> int {
    return lftBrdPadding;
}

auto ChessModel::getTopPadding() const -> int {
    return topBrdPadding;
}

auto ChessModel::getCellSize() const -> int {
    return cellSize;
}

auto ChessModel::GameOn() const -> bool {
    return isGameOn;
}

auto ChessModel::getCurrentPieces() const -> QList<PawnModel *> {
    return pieces;
}

auto ChessModel::getDeadPieces() const -> QList<PawnModel *> {
    return deadPieces;
}

auto ChessModel::isWhiteTurn() const -> bool {
    return isWhitePlayerTurn;
}

auto ChessModel::generateFEN() const -> QString {
    QString fen;
    int emptyCount = 0;

    // 1. Piece Placement
    for (int y = 7; y >= 0; y--) {
        for (int x = 0; x < 8; x++) {
            auto piece = findPieceAt(x, y);
            if (piece) {
                if (emptyCount > 0) {
                    fen += QString::number(emptyCount);
                    emptyCount = 0;
                }
                char pieceChar = pieceCharFromType(piece);
                fen += static_cast<char>((piece->isWhite) ? pieceChar : tolower(pieceChar));
            } else {
                emptyCount++;
            }
        }
        if (emptyCount > 0) {
            fen += QString::number(emptyCount);
            emptyCount = 0;
        }
        if (y != 0) {
            fen += "/";
        }
    }

    // 2. Side to Move
    fen += (isWhitePlayerTurn ? " w " : " b ");

    // 3. Castling Availability
    fen += "KQkq";

    // 4. En passant target square
    fen += " - ";

    // 5. Halfmove Clock
    fen += QString::number(fromLastKill) + " ";

    // 6. Fullmove Number
    fen += QString::number(turnNumber);

    return fen;
}

auto ChessModel::getMovesVector() -> QVector<BoardPosition> {
    if (currentlySelectedPawn) {
        pPawnMovesVector.append(currentlySelectedPawn->pwnBPosition);
    }
    return pPawnMovesVector;
}

auto ChessModel::ChangePiecePlace(quint8 x, quint8 y) -> void {
    bool canMove = false;
    for (const auto &move: pPawnMovesVector) {
        if (move.posX == x && move.posY == y) {
            canMove = true;
            break;
        }
    }

    if (canMove) {
        auto moveY = y;
        if (currentlySelectedPawn->allowSpecialMove.posX == x && currentlySelectedPawn->allowSpecialMove.posY == y &&
            x != 0) {
            y = y + (isWhitePlayerTurn ? -1 : 1);
        }
        if (currentlySelectedPawn->allowSpecialMove.posX == 20 && currentlySelectedPawn->allowSpecialMove.posY == 20) {
            if (std::abs(currentlySelectedPawn->pwnBPosition.posX - x) == 2) {
                performCastling(x);
            }
        }
        KillAtack(x, y);
        y = moveY;
        // Move the currently selected pawn to the new position
        auto oldY = currentlySelectedPawn->pwnBPosition.posY;
        currentlySelectedPawn->pwnBPosition.posX = x;
        currentlySelectedPawn->pwnBPosition.posY = y;
        clearEnPassants();
        if (currentlySelectedPawn->CleanUp() && std::abs(y - oldY) == 2) {
            for (auto *pawn: pieces) {
                if (std::abs(pawn->pwnBPosition.posX - x) == 1 && pawn->pwnBPosition.posY == y &&
                    pawn->isWhite != isWhitePlayerTurn) {
                    pawn->allowSpecialMove = {x, static_cast<quint8>(y + (isWhitePlayerTurn ? -1 : 1))};
                }
            }
        }
        //qDebug() << currentlySelectedPawn->imagePath;
        if (currentlySelectedPawn->imagePath == ":/pieces-png/white-pawn.png" ||
            currentlySelectedPawn->imagePath == ":/pieces-png/black-pawn.png") {
            fromLastKill = -1;
        }
        if (currentlySelectedPawn->isUpgradable) {
            PromotePawn();
        }
        // Switch the turn
        if (!currentlySelectedPawn->isWhite) {
            turnNumber++;
        }
        fromLastKill++;
        isWhitePlayerTurn = !isWhitePlayerTurn;
        currentlySelectedPawn = nullptr;
        pPawnMovesVector.clear();
    } else {
        pPawnMovesVector.clear();
        getPieceClicked(x, y);
    }
}

auto ChessModel::startGame() -> void {
    isGameOn = true;
}

auto ChessModel::stopGame() -> void {
    isGameOn = false;
}

auto ChessModel::popCurrentPieceFromMoves() -> void {
    if (!pPawnMovesVector.isEmpty()) {
        pPawnMovesVector.pop_back();
    }
}

auto ChessModel::isPieceSelected() -> bool {
    if (currentlySelectedPawn) {
        return true;
    } else {
        return false;
    }
}

auto ChessModel::isKingAttacked() -> bool {
    auto currentKing = isWhitePlayerTurn ? whiteKing : blackKing;
    return (isCellAttacked(currentKing->pwnBPosition.posX, currentKing->pwnBPosition.posY));
}

auto ChessModel::getPieceClicked(quint8 column, quint8 row) -> void {
    for (auto *piece: pieces) {
        if (piece->pwnBPosition.posX == column && piece->pwnBPosition.posY == row &&
            piece->isWhite == isWhitePlayerTurn) {
            if (currentlySelectedPawn == piece) {
                break;
            }
            currentlySelectedPawn = piece;
            updateMoveVector(piece);
            return;
        }
    }
    currentlySelectedPawn = nullptr;
}

auto ChessModel::isCellAttacked(quint8 column, quint8 row) -> bool {
    auto breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (row + i <= 7) {
            for (const auto &pawn: pieces) {
                if (column == pawn->pwnBPosition.posX &&
                    row + i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (column + i <= 7) {
            for (const auto &pawn: pieces) {
                if (column + i == pawn->pwnBPosition.posX &&
                    row == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (row >= i) {
            for (const auto &pawn: pieces) {
                if (column == pawn->pwnBPosition.posX &&
                    row - i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (row >= i) {
            for (const auto &pawn: pieces) {
                if (column - i == pawn->pwnBPosition.posX &&
                    row == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (column + i <= 7 && row + i <= 7) {
            for (const auto &pawn: pieces) {
                if (column + i == pawn->pwnBPosition.posX &&
                    row + i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (column + i <= 7 && row >= i) {
            for (const auto &pawn: pieces) {
                if (column + i == pawn->pwnBPosition.posX &&
                    row - i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (column >= i && row >= i) {
            for (const auto &pawn: pieces) {
                if (column - i == pawn->pwnBPosition.posX &&
                    row - i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (column >= i && row + i <= 7) {
            for (const auto &pawn: pieces) {
                if (column - i == pawn->pwnBPosition.posX &&
                    row + i == pawn->pwnBPosition.posY) {
                    if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                        return true;
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
    }

    int knightMovesX[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int knightMovesY[] = {1, 2, 2, 1, -1, -2, -2, -1};
    for (const auto &pawn: pieces) {
        for (auto i = int{0}; i < 8; i++) {
            if (column + knightMovesX[i] == pawn->pwnBPosition.posX &&
                row + knightMovesY[i] == pawn->pwnBPosition.posY) {
                if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {
                    return true;
                }
            }
        }
    }
    return false;
}

auto ChessModel::isMate() -> bool {
    auto tempMoves = pPawnMovesVector;
    for (auto *piece: pieces) {
        if (piece->isWhite == isWhitePlayerTurn) {
            updateMoveVector(piece);
            if (!pPawnMovesVector.isEmpty()) {
                pPawnMovesVector = tempMoves;
                return false;
            }
        }
    }
    pPawnMovesVector = tempMoves;
    return true;
}

auto ChessModel::pieceCharFromType(const PawnModel *piece) -> char {
    if (dynamic_cast<const KingModel *>(piece)) return 'K';
    if (dynamic_cast<const QueenModel *>(piece)) return 'Q';
    if (dynamic_cast<const RookModel *>(piece)) return 'R';
    if (dynamic_cast<const BishopModel *>(piece)) return 'B';
    if (dynamic_cast<const KnightModel *>(piece)) return 'N';
    if (dynamic_cast<const PawnModel *>(piece)) return 'P';
    return '?';  // should not happen
}

auto ChessModel::findPieceAt(int x, int y) const -> PawnModel * {
    for (auto *piece: pieces) {
        if (piece->pwnBPosition.posX == x && piece->pwnBPosition.posY == y) {
            return piece;
        }
    }
    return nullptr; // No piece at this position
}

auto ChessModel::initializePieces(QList<PawnModel *> &allPieces, PawnModel *&whiteKing, PawnModel *&blackKing) -> void {
    auto piecePosition = BoardPosition{0, 0};
    auto rookWhite1 = new RookModel(piecePosition, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite1);
    piecePosition = {7, 0};
    auto rookWhite2 = new RookModel(piecePosition, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite2);

    piecePosition = {1, 0};
    auto knightWhite1 = new KnightModel(piecePosition, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite1);
    piecePosition = {6, 0};
    auto knightWhite2 = new KnightModel(piecePosition, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite2);

    piecePosition = {2, 0};
    auto bishopWhite1 = new BishopModel(piecePosition, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite1);
    piecePosition = {5, 0};
    auto bishopWhite2 = new BishopModel(piecePosition, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite2);

    piecePosition = {3, 0};
    auto queenWhite = new QueenModel(piecePosition, ":/pieces-png/white-queen.png");
    allPieces.append(queenWhite);

    piecePosition = {4, 0};
    auto kingWhite = new KingModel(piecePosition, ":/pieces-png/white-king.png");
    allPieces.append(kingWhite);

    for (auto i = quint8{0}; i < 8; i++) {
        piecePosition = {i, 1};
        auto pawnPiece = new PawnModel(piecePosition, ":/pieces-png/white-pawn.png");
        allPieces.append(pawnPiece);
    }


    piecePosition = {0, 7};
    auto rookBlack1 = new RookModel(piecePosition, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack1);
    piecePosition = {7, 7};
    auto rookBlack2 = new RookModel(piecePosition, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack2);

    piecePosition = {1, 7};
    auto knightBlack1 = new KnightModel(piecePosition, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack1);
    piecePosition = {6, 7};
    auto knightBlack2 = new KnightModel(piecePosition, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack2);

    piecePosition = {2, 7};
    auto bishopBlack1 = new BishopModel(piecePosition, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack1);
    piecePosition = {5, 7};
    auto bishopBlack2 = new BishopModel(piecePosition, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack2);

    piecePosition = {3, 7};
    auto queenBlack = new QueenModel(piecePosition, ":/pieces-png/black-queen.png", false);
    allPieces.append(queenBlack);

    piecePosition = {4, 7};
    auto kingBlack = new KingModel(piecePosition, ":/pieces-png/black-king.png", false);
    allPieces.append(kingBlack);

    for (auto i = quint8{0}; i < 8; i++) {
        piecePosition = {i, 6};
        auto pawnPiece = new PawnModel(piecePosition, ":/pieces-png/black-pawn.png", false);
        allPieces.append(pawnPiece);
    }
    whiteKing = kingWhite;
    blackKing = kingBlack;

}

auto ChessModel::updateMoveVector(PawnModel *pChosenPawn) -> void {
    if (!pPawnMovesVector.isEmpty()) {
        pPawnMovesVector.clear();
    }

    pChosenPawn->PossibleMoves(&pPawnMovesVector, pieces);
    auto correctPosition = pChosenPawn->pwnBPosition;
    pPawnMovesVector.erase(std::remove_if(pPawnMovesVector.begin(), pPawnMovesVector.end(), [&](const auto &move) {
        // Simulate the move
        pChosenPawn->pwnBPosition = move;
        // Find if there is a piece at the move position and temporarily remove it
        PawnModel *capturedPiece = nullptr;
        int capturedPieceIndex = -1;
        for (auto i = int{0}; i < pieces.size(); i++) {

            if (pieces.at(i)->pwnBPosition.posX == move.posX && pieces.at(i)->pwnBPosition.posY == move.posY &&
                pieces.at(i) != pChosenPawn && pieces.at(i)->isWhite != isWhitePlayerTurn) {
                capturedPiece = pieces.at(i);
                capturedPieceIndex = i;
                pieces.removeAt(i);
                break;
            }
        }
        // Check if the king is in check after the move
        bool isKingInCheck = isWhitePlayerTurn ?
                             isCellAttacked(whiteKing->pwnBPosition.posX, whiteKing->pwnBPosition.posY) :
                             isCellAttacked(blackKing->pwnBPosition.posX, blackKing->pwnBPosition.posY);
        // Undo the move
        pChosenPawn->pwnBPosition = correctPosition;

        // Restore the captured piece if there was one
        if (capturedPiece && capturedPieceIndex != -1) {
            pieces.insert(capturedPieceIndex, capturedPiece);
        }
        return isKingInCheck;
    }), pPawnMovesVector.end());
}

auto ChessModel::performCastling(quint8 x) -> void {
    bool isKingside = x > currentlySelectedPawn->pwnBPosition.posX;
    quint8 rookOriginalX = isKingside ? 7 : 0;  // Assuming rook is at the original position
    quint8 rookNewX = isKingside ? x - 1 : x + 1;  // Rook's new position after castling

    // Find the rook and update its position
    auto rookIt = std::find_if(pieces.begin(), pieces.end(), [rookOriginalX, this](const PawnModel *piece) {
        return piece->pwnBPosition.posX == rookOriginalX &&
               piece->pwnBPosition.posY == currentlySelectedPawn->pwnBPosition.posY &&
               piece->imagePath == (isWhitePlayerTurn ? ":/pieces-png/white-rook.png" : ":/pieces-png/black-rook.png");
    });

    if (rookIt != pieces.end()) {
        (*rookIt)->pwnBPosition.posX = rookNewX;  // Update rook's position
    }
}

auto ChessModel::PromotePawn() -> void {
    if (currentlySelectedPawn->isWhite) {
        auto newQueen = new QueenModel(currentlySelectedPawn->pwnBPosition, ":/pieces-png/white-queen.png");
        pieces.append(newQueen);
    } else {
        auto newQueen = new QueenModel(currentlySelectedPawn->pwnBPosition, ":/pieces-png/black-queen.png", false);
        pieces.append(newQueen);
    }
    auto deletePawn = std::find(pieces.begin(), pieces.end(), currentlySelectedPawn);
    if (deletePawn != pieces.end()) {
        delete *deletePawn; // Delete the object
        pieces.erase(deletePawn); // Remove the pointer to the object from the list
    }
}

auto ChessModel::KillAtack(quint8 x, quint8 y) -> void {
    auto it = std::find_if(pieces.begin(), pieces.end(), [x, y](const PawnModel *piece) {
        return piece->pwnBPosition.posX == x && piece->pwnBPosition.posY == y;
    });

    if (it != pieces.end()) {
        deadPieces.append(*it); // If there is a piece at the destination, capture it (add to deadPieces)
        pieces.erase(it);
        fromLastKill = 0;
    }
}

auto ChessModel::clearEnPassants() -> void {
    for (auto *pawn: pieces) {
        if (!pawn->isFirstMove) {
            pawn->allowSpecialMove = {};
        }
    }
}

ChessModel::~ChessModel() {
    for (auto *piece: pieces) {
        delete piece;
    }
    pieces.clear();

    for (auto *piece: deadPieces) {
        delete piece;
    }
    deadPieces.clear();
}







