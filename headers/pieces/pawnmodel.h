#ifndef QTCHESS_PJC_PAWNMODEL_H
#define QTCHESS_PJC_PAWNMODEL_H

//#include <QtCore/QDebug>
#include "../boardposition.h"
#include <QVector>
#include <memory>

class PawnModel {

public:
    PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    virtual auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void;

    virtual auto ValidateMove(int x, int y) -> bool;

    virtual auto CleanUp() -> bool;

    virtual ~PawnModel() = default;

    bool isUpgradable;
    BoardPosition pwnBPosition;
    QString imagePath;
    bool isWhite;
    BoardPosition allowSpecialMove{};
    bool isFirstMove;
};

#endif //QTCHESS_PJC_PAWNMODEL_H
