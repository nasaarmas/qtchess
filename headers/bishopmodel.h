//
// Created by Bartek on 9/10/2023.
//

#ifndef QTCHESS_PJC_BISHOPMODEL_H
#define QTCHESS_PJC_BISHOPMODEL_H

#include "pawnmodel.h"

class BishopModel : public PawnModel{
public:
    BishopModel(BoardPosition pwnBPosition, QString imagePath);

};

#endif //QTCHESS_PJC_BISHOPMODEL_H
