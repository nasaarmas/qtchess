#ifndef QTCHESS_PJC_CHESSMODEL_H
#define QTCHESS_PJC_CHESSMODEL_H

#include "pawnmodel.h"
#include "bishopmodel.h"
#include "rookmodel.h"
#include "knightmodel.h"
#include "queenmodel.h"
#include "kingmodel.h"


class ChessModel {
public:
    ChessModel();
    ~ChessModel();
    [[nodiscard]] QList<PawnModel *> getCurrentPieces() const;

private:
    static void initializePieces(QList<PawnModel *> &allPieces);
    QList<PawnModel *> pieces;
};

#endif //QTCHESS_PJC_CHESSMODEL_H
