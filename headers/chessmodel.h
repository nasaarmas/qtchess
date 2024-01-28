#ifndef QTCHESS_PJC_CHESSMODEL_H
#define QTCHESS_PJC_CHESSMODEL_H

#include <QList>
#include <QDebug>
#include "pawnmodel.h"
#include "bishopmodel.h"
#include "rookmodel.h"
#include "knightmodel.h"
#include "queenmodel.h"
#include "kingmodel.h"


class ChessModel {
public:
    ChessModel();

    [[nodiscard]] int getLftPadding() const;

    [[nodiscard]] int getTopPadding() const;

    [[nodiscard]] int getCellSize() const;

    [[nodiscard]] QList<PawnModel *> getCurrentPieces() const;
    [[nodiscard]] QList<PawnModel *> getDeadPieces() const;

    [[nodiscard]] QVector<BoardPosition> getMovesVector() const;

    void ChangePiecePlace(quint8 x, quint8 y);

    bool IsPieceSelected();

    void getPieceClicked(quint8 column, quint8 row);

    void isMoveValid(quint8 column, quint8 row);
    //void unselectPiece();


    ~ChessModel();

private:
    void updateMoveVector(PawnModel *pChosenPawn);

    static void initializePieces(QList<PawnModel *> &allPieces);

    QVector<BoardPosition> pPawnMovesVector;
    QList<PawnModel *> pieces;
    QList<PawnModel *> deadPieces;
    PawnModel *currentlySelectedPawn;
    int fontSize, lftBrdPadding, topBrdPadding, cellSize;
};

#endif //QTCHESS_PJC_CHESSMODEL_H
