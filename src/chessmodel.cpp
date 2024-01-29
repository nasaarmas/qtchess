#include "../headers/chessmodel.h"


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
}

ChessModel::~ChessModel() {
    for (PawnModel *piece: this->pieces) {
        delete piece;
    }
    pieces.clear();
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

auto ChessModel::getMovesVector() const -> QVector<BoardPosition> {
    return pPawnMovesVector;
}

auto ChessModel::ChangePiecePlace(quint8 x, quint8 y) -> void {
    if (!pPawnMovesVector.isEmpty()) {
        pPawnMovesVector.pop_back();
    }

    bool canMove = false;
    for (const auto &move: pPawnMovesVector) {
        if (move.posX == x && move.posY == y) {
            canMove = true;
            break;
        }
    }

    if (canMove) {
        auto moveY = y;
        if (currentlySelectedPawn->allowSpecialMove.posX == x && currentlySelectedPawn->allowSpecialMove.posY == y) {
            y = y + (isWhitePlayerTurn ? -1 : 1);
        }
        // Check if there is a piece in the destination cell to capture it
        auto it = std::find_if(pieces.begin(), pieces.end(), [x, y](const PawnModel *piece) {
            return piece->pwnBPosition.posX == x && piece->pwnBPosition.posY == y;
        });

        if (it != pieces.end()) {
            // If there is a piece at the destination, capture it (add to deadPieces)
            deadPieces.append(*it);
            pieces.erase(it);
        }
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
        // Switch the turn
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

auto ChessModel::isPieceSelected() -> bool {
    if (currentlySelectedPawn) {
        return true;
    } else {
        return false;
    }
}

auto ChessModel::getPieceClicked(quint8 column, quint8 row) -> void {
    for (auto *piece: pieces) {
        if (piece->pwnBPosition.posX == column && piece->pwnBPosition.posY == row &&
            piece->isWhite == isWhitePlayerTurn) {
            if (currentlySelectedPawn == piece) {
                currentlySelectedPawn = nullptr;
                return;
            }
            currentlySelectedPawn = piece;
            updateMoveVector(piece);
            return;
        }
    }
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

    breakOuterLoop = false;
    int knightMovesX[] = {2, 1, -1, -2, -2, -1, 1, 2};
    int knightMovesY[] = {1, 2, 2, 1, -1, -2, -2, -1};
    for (const auto &pawn: pieces) {
        for (auto i = int{0}; i < 8; i++) {
            if (column + knightMovesX[i] == pawn->pwnBPosition.posX &&
                row + knightMovesY[i] == pawn->pwnBPosition.posY) {
                if (isWhitePlayerTurn != pawn->isWhite && pawn->ValidateMove(int(column), int(row))) {

                    return true;

                }
                breakOuterLoop = true;
                break;
            }
        }
        if (breakOuterLoop) {
            break;
        }
    }
    return false;
}

auto ChessModel::isMate() -> bool {
    PawnModel *currentKing = isWhitePlayerTurn ? whiteKing : blackKing;
    QVector<BoardPosition> tempMoves = {};
    currentKing->PossibleMoves(&tempMoves, pieces);

    // Check if the king can move out of the check
    auto correctPosition = currentKing->pwnBPosition;
    tempMoves.erase(std::remove_if(tempMoves.begin(), tempMoves.end(), [&](const auto &move) {
        currentKing->pwnBPosition = move;
        auto attacked = isCellAttacked(currentKing->pwnBPosition.posX, currentKing->pwnBPosition.posY);
        currentKing->pwnBPosition = correctPosition;
        return attacked;
    }), tempMoves.end());

    if (!tempMoves.isEmpty() || !isCellAttacked(currentKing->pwnBPosition.posX, currentKing->pwnBPosition.posY)) {
        return false; // King can move to a safe position or is not in check
    }

    // Check if any piece can block the check or capture the threatening piece
    for (auto *piece: pieces) {
        if (piece->isWhite == isWhitePlayerTurn) {
            QVector<BoardPosition> pieceMoves = {};
            piece->PossibleMoves(&pieceMoves, pieces);
            for (const auto &move: pieceMoves) {
                auto originalPosition = piece->pwnBPosition;
                piece->pwnBPosition = move;

                // Simulate capturing an opponent's piece
                PawnModel *capturedPiece = nullptr;
                auto it = std::find_if(pieces.begin(), pieces.end(), [move](const PawnModel *otherPiece) {
                    return otherPiece->pwnBPosition.posX == move.posX && otherPiece->pwnBPosition.posY == move.posY;
                });
                if (it != pieces.end() && (*it)->isWhite != isWhitePlayerTurn) {
                    capturedPiece = *it;
                    pieces.erase(it);
                }
                auto kingIsAttacked = isCellAttacked(currentKing->pwnBPosition.posX, currentKing->pwnBPosition.posY);
                // Undo the move and restore captured piece if any
                piece->pwnBPosition = originalPosition;
                if (capturedPiece) {
                    pieces.push_back(capturedPiece);
                }
                if (!kingIsAttacked) {
                    return false; // A piece can block the check or capture the threatening piece
                }
            }
        }
    }

    qDebug() << "Game over: " << (isWhitePlayerTurn ? "Black wins" : "White wins");
    isGameOn = false;
    return true; // Checkmate
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
    if (!pPawnMovesVector.empty()) {
        pPawnMovesVector.clear();
    }

    pChosenPawn->PossibleMoves(&pPawnMovesVector, pieces);
    auto correctPosition = currentlySelectedPawn->pwnBPosition;
    pPawnMovesVector.erase(std::remove_if(pPawnMovesVector.begin(), pPawnMovesVector.end(), [&](const auto &move) {
        // Simulate the move
        currentlySelectedPawn->pwnBPosition = move;
        // Find if there is a piece at the move position and temporarily remove it
        PawnModel *capturedPiece = nullptr;
        for (auto it = pieces.begin(); it != pieces.end(); ++it) {
            if ((*it)->pwnBPosition.posX == move.posX && (*it)->pwnBPosition.posY == move.posY &&
                *it != currentlySelectedPawn) {
                capturedPiece = *it;
                pieces.erase(it);
                break;
            }
        }
        // Check if the king is in check after the move
        bool isKingInCheck = isWhitePlayerTurn ?
                             isCellAttacked(whiteKing->pwnBPosition.posX, whiteKing->pwnBPosition.posY) :
                             isCellAttacked(blackKing->pwnBPosition.posX, blackKing->pwnBPosition.posY);
        // Undo the move
        currentlySelectedPawn->pwnBPosition = correctPosition;

        // Restore the captured piece if there was one
        if (capturedPiece) {
            pieces.push_back(capturedPiece);
        }
        return isKingInCheck;
    }), pPawnMovesVector.end());

    pPawnMovesVector.append(currentlySelectedPawn->pwnBPosition);
}

auto ChessModel::clearEnPassants() -> void {
    for (auto *pawn: pieces) {
        if (!pawn->isFirstMove) {
            pawn->allowSpecialMove = {};
        }
    }
}






