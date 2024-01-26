#ifndef QTCHESS_PJC_BISHOPMODEL_H
#define QTCHESS_PJC_BISHOPMODEL_H

#include "pawnmodel.h"

class BishopModel : public PawnModel {
public:
    BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true, bool isAlive = true);

    void movePiece() override;
};

#endif //QTCHESS_PJC_BISHOPMODEL_H
