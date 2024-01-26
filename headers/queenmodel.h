#ifndef QTCHESS_PJC_QUEENMODEL_H
#define QTCHESS_PJC_QUEENMODEL_H

#include "pawnmodel.h"

class QueenModel : public PawnModel {
public:
    QueenModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true, bool isAlive = true);

    void movePiece() override;
};

#endif //QTCHESS_PJC_QUEENMODEL_H
