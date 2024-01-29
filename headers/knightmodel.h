#ifndef QTCHESS_PJC_KNIGHTMODEL_H
#define QTCHESS_PJC_KNIGHTMODEL_H

#include "pawnmodel.h"
#include <QList>

class KnightModel : public PawnModel {
public:
    KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    bool ValidateMove(int x, int y) override;

    void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) override;
};


#endif //QTCHESS_PJC_KNIGHTMODEL_H
