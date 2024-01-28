//
// Created by Bartek on 26-Jan-24.
//

#ifndef QTCHESS_PJC_ROOKMODEL_H
#define QTCHESS_PJC_ROOKMODEL_H

#include <QList>
#include "pawnmodel.h"

class RookModel : public PawnModel {
public:
    RookModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) override;
};


#endif //QTCHESS_PJC_ROOKMODEL_H
