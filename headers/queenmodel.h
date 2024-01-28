#ifndef QTCHESS_PJC_QUEENMODEL_H
#define QTCHESS_PJC_QUEENMODEL_H

#include <QList>
#include "pawnmodel.h"

class QueenModel : public PawnModel {
public:
    QueenModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) override;
};

#endif //QTCHESS_PJC_QUEENMODEL_H
