#ifndef QTCHESS_PJC_KINGMODEL_H
#define QTCHESS_PJC_KINGMODEL_H

#include "pawnmodel.h"

class KingModel : public PawnModel {
public:
    KingModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true, bool isAlive = true);

    void movePiece() override;
};


#endif //QTCHESS_PJC_KINGMODEL_H
