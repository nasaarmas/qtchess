//
// Created by Bartek on 26-Jan-24.
//

#ifndef QTCHESS_PJC_ROOKMODEL_H
#define QTCHESS_PJC_ROOKMODEL_H

#include "pawnmodel.h"

class RookModel : public PawnModel{
public:
    RookModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite=true, bool isAlive=true);
    void movePiece() override;
};



#endif //QTCHESS_PJC_ROOKMODEL_H
