//
// Created by Bartek on 26-Jan-24.
//

#ifndef QTCHESS_PJC_KNIGHTMODEL_H
#define QTCHESS_PJC_KNIGHTMODEL_H

#include "pawnmodel.h"

class KnightModel : public PawnModel{
public:
    KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite=true, bool isAlive=true);
    void movePiece() override;
};



#endif //QTCHESS_PJC_KNIGHTMODEL_H
