#include <utility>

#include "../headers/knightmodel.h"


KnightModel::KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite) {};

void KnightModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) {
    if (pwnBPosition.posX >= 2) {
        if (pwnBPosition.posY + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 2), static_cast<quint8>(pwnBPosition.posY + 1)});
        }
        if (pwnBPosition.posY >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 2), static_cast<quint8>(pwnBPosition.posY - 1)});
        }
    }

    if (pwnBPosition.posX + 2 <= 7) {
        if (pwnBPosition.posY + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 2), static_cast<quint8>(pwnBPosition.posY + 1)});
        }
        if (pwnBPosition.posY >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 2), static_cast<quint8>(pwnBPosition.posY - 1)});
        }
    }

    if (pwnBPosition.posY + 2 <= 7) {
        if (pwnBPosition.posX + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 1), static_cast<quint8>(pwnBPosition.posY + 2)});
        }
        if (pwnBPosition.posX >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 1), static_cast<quint8>(pwnBPosition.posY + 2)});
        }
    }

    if (pwnBPosition.posY >= 2) {
        if (pwnBPosition.posX + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 1), static_cast<quint8>(pwnBPosition.posY - 2)});
        }
        if (pwnBPosition.posX >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 1), static_cast<quint8>(pwnBPosition.posY - 2)});
        }
    }
    for (const auto &pawn: pieces) {
        for (auto i{0}; i < moveVector->size(); i++) {
            if (pawn->pwnBPosition.posX == moveVector->at(i).posX &&
                pawn->pwnBPosition.posY == moveVector->at(i).posY &&
                isWhite == pawn->isWhite) {
                moveVector->remove(i);
            }
        }
    }
}