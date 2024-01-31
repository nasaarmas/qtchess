#ifndef QTCHESS_PJC_QUEENMODEL_H
#define QTCHESS_PJC_QUEENMODEL_H

#include <QList>
#include "pawnmodel.h"

class QueenModel : public PawnModel {
public:
    QueenModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    auto ValidateMove(int x, int y) -> bool override;

    auto CleanUp() -> bool override;
};

#endif //QTCHESS_PJC_QUEENMODEL_H
