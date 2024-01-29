#ifndef QTCHESS_PJC_BISHOPMODEL_H
#define QTCHESS_PJC_BISHOPMODEL_H

#include "pawnmodel.h"

class BishopModel : public PawnModel {
public:
    BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    void PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) override;
    void CleanUp() override;
    bool ValidateMove(int x, int y) override;
};

#endif //QTCHESS_PJC_BISHOPMODEL_H
