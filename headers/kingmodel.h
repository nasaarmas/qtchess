#ifndef QTCHESS_PJC_KINGMODEL_H
#define QTCHESS_PJC_KINGMODEL_H

#include <QList>
#include "pawnmodel.h"

class KingModel : public PawnModel {
public:
    KingModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) override;
};


#endif //QTCHESS_PJC_KINGMODEL_H
