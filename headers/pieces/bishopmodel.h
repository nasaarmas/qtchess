#ifndef QTCHESS_PJC_BISHOPMODEL_H
#define QTCHESS_PJC_BISHOPMODEL_H

#include "pawnmodel.h"

class BishopModel : public PawnModel {
public:
    BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    auto CleanUp() -> bool override;

    auto ValidateMove(int x, int y) -> bool override;
};

#endif //QTCHESS_PJC_BISHOPMODEL_H
