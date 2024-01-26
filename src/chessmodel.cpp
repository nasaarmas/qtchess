#include "../headers/chessmodel.h"


ChessModel::ChessModel() {
    initializePieces(this->pieces);
}


void ChessModel::initializePieces(QList<PawnModel *> &allPieces) {
    auto piecePosition = BoardPosition{1, 1};
    auto rookWhite1 = new RookModel(piecePosition, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite1);
    piecePosition = {8, 1};
    auto rookWhite2 = new RookModel(piecePosition, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite2);

    piecePosition = {2, 1};
    auto knightWhite1 = new KnightModel(piecePosition, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite1);
    piecePosition = {7, 1};
    auto knightWhite2 = new KnightModel(piecePosition, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite2);

    piecePosition = {3, 1};
    auto bishopWhite1 = new BishopModel(piecePosition, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite1);
    piecePosition = {6, 1};
    auto bishopWhite2 = new BishopModel(piecePosition, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite2);

    piecePosition = {4, 1};
    auto queenWhite = new QueenModel(piecePosition, ":/pieces-png/white-queen.png");
    allPieces.append(queenWhite);

    piecePosition = {5, 1};
    auto kingWhite = new KingModel(piecePosition, ":/pieces-png/white-king.png");
    allPieces.append(kingWhite);

    for (auto i = quint8{1}; i <= 8; i++) {
        piecePosition = {i, 2};
        auto pawnPiece = new PawnModel(piecePosition, ":/pieces-png/white-pawn.png");
        allPieces.append(pawnPiece);
    }


    piecePosition = {1, 8};
    auto rookBlack1 = new RookModel(piecePosition, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack1);
    piecePosition = {8, 8};
    auto rookBlack2 = new RookModel(piecePosition, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack2);

    piecePosition = {2, 8};
    auto knightBlack1 = new KnightModel(piecePosition, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack1);
    piecePosition = {7, 8};
    auto knightBlack2 = new KnightModel(piecePosition, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack2);

    piecePosition = {3, 8};
    auto bishopBlack1 = new BishopModel(piecePosition, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack1);
    piecePosition = {6, 8};
    auto bishopBlack2 = new BishopModel(piecePosition, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack2);

    piecePosition = {4, 8};
    auto queenBlack = new QueenModel(piecePosition, ":/pieces-png/black-queen.png", false);
    allPieces.append(queenBlack);

    piecePosition = {5, 8};
    auto kingBlack = new KingModel(piecePosition, ":/pieces-png/black-king.png");
    allPieces.append(kingBlack);

    for (auto i = quint8{1}; i <= 8; i++) {
        piecePosition = {i, 7};
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

QList<PawnModel *> ChessModel::getCurrentPieces() const {
    return pieces;
}


