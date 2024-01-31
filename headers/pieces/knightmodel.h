#ifndef QTCHESS_PJC_KNIGHTMODEL_H
#define QTCHESS_PJC_KNIGHTMODEL_H

#include "pawnmodel.h"
#include <QList>

class KnightModel : public PawnModel {
public:
    KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    auto ValidateMove(int x, int y) -> bool override;

    auto CleanUp() -> bool override;
};


#endif //QTCHESS_PJC_KNIGHTMODEL_H
