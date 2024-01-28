#include "../headers/chessmodel.h"


ChessModel::ChessModel() {
    initializePieces(this->pieces);
    fontSize = 14;
    lftBrdPadding = 200;
    topBrdPadding = 150;
    cellSize = 50;
    pPawnMovesVector = {};
    currentlySelectedPawn = nullptr;
    deadPieces = {};
}

void ChessModel::initializePieces(QList<PawnModel *> &allPieces) {
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
}

ChessModel::~ChessModel() {
    for (PawnModel *piece: this->pieces) {
        delete piece;
    }
    // Clear the list
    pieces.clear();
}

QList<PawnModel *> ChessModel::getDeadPieces() const {
    return deadPieces;
}

QList<PawnModel *> ChessModel::getCurrentPieces() const {
    return pieces;
}

int ChessModel::getLftPadding() const {
    return lftBrdPadding;
}

int ChessModel::getTopPadding() const {
    return topBrdPadding;
}

int ChessModel::getCellSize() const {
    return cellSize;
}

void ChessModel::getPieceClicked(quint8 column, quint8 row) {
    for (auto *piece: pieces) {
        if (piece->pwnBPosition.posX == column && piece->pwnBPosition.posY == row) {
            currentlySelectedPawn = piece;
            updateMoveVector(piece);
            return;
        }
    }
}

QVector<BoardPosition> ChessModel::getMovesVector() const {
    return pPawnMovesVector;
}

void ChessModel::updateMoveVector(PawnModel *pChosenPawn) {
    if (!pPawnMovesVector.empty()) {
        pPawnMovesVector.clear();
    }
    pChosenPawn->PossibleMoves(&pPawnMovesVector, pieces);

}

void ChessModel::ChangePiecePlace(quint8 x, quint8 y) {
    bool canDo = false;
    for (const auto &move: pPawnMovesVector) {
        if (move.posX == x && move.posY == y) {
            canDo = true;
            break;
        }
    }
    if (canDo) {
        for (auto it = pieces.begin(); it != pieces.end(); ++it) {
            auto *piece = *it;

            if (piece->pwnBPosition.posX == x && piece->pwnBPosition.posY == y) {
                qDebug() << "am i even here \n";
                deadPieces.append(piece);
                pieces.erase(it);
                break;
            }
        }
        currentlySelectedPawn->pwnBPosition.posX = x;
        currentlySelectedPawn->pwnBPosition.posY = y;
        currentlySelectedPawn->CleanUp();
    }
    currentlySelectedPawn = nullptr;
    pPawnMovesVector.clear();

}

bool ChessModel::IsPieceSelected() {
    if (currentlySelectedPawn) {
        return true;
    } else {
        return false;
    }
}

void ChessModel::isMoveValid(quint8 column, quint8 row) {

}


