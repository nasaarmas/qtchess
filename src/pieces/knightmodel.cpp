#include <utility>

#include "../../headers/pieces/knightmodel.h"


KnightModel::KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite) {};

auto KnightModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void {
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
                i--;
            }
        }
    }
}

auto KnightModel::ValidateMove(int x, int y) -> bool {
    return (((std::abs(x - int{pwnBPosition.posX}) == 1 && std::abs(y - int{pwnBPosition.posY}) == 2)) ||
            ((std::abs(x - int{pwnBPosition.posX}) == 2 && std::abs(y - int{pwnBPosition.posY}) == 1)));
}

auto KnightModel::CleanUp() -> bool {
    return false;
}
