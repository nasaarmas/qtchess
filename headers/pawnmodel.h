//
// Created by Bartek on 9/9/2023.
//

#ifndef QTCHESS_PJC_PAWNMODEL_H
#define QTCHESS_PJC_PAWNMODEL_H

#include <QtCore/QDebug>
#include "boardposition.h"

class PawnModel {

public:
    PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite=true, bool isAlive=true);
    virtual void movePiece();
    BoardPosition pwnBPosition;
    QString imagePath;
    bool isWhite;
    bool isAlive;

    virtual ~PawnModel() = default;

};
#endif //QTCHESS_PJC_PAWNMODEL_H
