#ifndef QTCHESS_PJC_PAWNMODEL_H
#define QTCHESS_PJC_PAWNMODEL_H

//#include <QtCore/QDebug>
#include "boardposition.h"
#include <QVector>
#include <memory>

class PawnModel {

public:
    PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    virtual void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces);

    virtual void CleanUp();

    BoardPosition pwnBPosition;
    QString imagePath;
    bool isWhite;
    bool isFirstMove;

    virtual ~PawnModel() = default;

};

#endif //QTCHESS_PJC_PAWNMODEL_H
