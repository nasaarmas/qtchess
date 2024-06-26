#include "../../headers/pieces/pawnmodel.h"
#include <QDebug>
#include <utility>

PawnModel::PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) :
        pwnBPosition(pwnBPosition), imagePath(std::move(imagePath)), isWhite(isWhite) {
    this->isFirstMove = true;
    this->allowSpecialMove = {};
    isUpgradable = false;
}

auto PawnModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void {
    if (isWhite) {
        if (pwnBPosition.posY < 7) {
            moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY + 1)});
        }
        if (isFirstMove) {
            moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY + 2)});
        }

        for (const auto &pawn: pieces) {
            if (pawn->pwnBPosition.posX == pwnBPosition.posX - 1 && pawn->pwnBPosition.posY == pwnBPosition.posY + 1 &&
                isWhite != pawn->isWhite) {
                moveVector->append({pawn->pwnBPosition.posX, pawn->pwnBPosition.posY});
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX + 1 && pawn->pwnBPosition.posY == pwnBPosition.posY + 1 &&
                isWhite != pawn->isWhite) {
                moveVector->append({pawn->pwnBPosition.posX, pawn->pwnBPosition.posY});
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX && pawn->pwnBPosition.posY == pwnBPosition.posY + 2 &&
                isFirstMove) {
                moveVector->remove(1);
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX && pawn->pwnBPosition.posY == pwnBPosition.posY + 1) {
                if (isFirstMove) {
                    moveVector->remove(1);
                }
                moveVector->remove(0);
            }
        }
    } else {
        if (pwnBPosition.posY < 7) {
            moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY - 1)});
        }
        if (isFirstMove) {
            moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY - 2)});
        }

        for (const auto &pawn: pieces) {
            if (pawn->pwnBPosition.posX == pwnBPosition.posX - 1 && pawn->pwnBPosition.posY == pwnBPosition.posY - 1 &&
                isWhite != pawn->isWhite) {
                moveVector->append({pawn->pwnBPosition.posX, pawn->pwnBPosition.posY});
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX + 1 && pawn->pwnBPosition.posY == pwnBPosition.posY - 1 &&
                isWhite != pawn->isWhite) {
                moveVector->append({pawn->pwnBPosition.posX, pawn->pwnBPosition.posY});
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX && pawn->pwnBPosition.posY == pwnBPosition.posY - 2 &&
                isFirstMove) {
                moveVector->remove(1);
            }
            if (pawn->pwnBPosition.posX == pwnBPosition.posX && pawn->pwnBPosition.posY == pwnBPosition.posY - 1) {
                moveVector->remove(0);
            }
        }
    }
    if (allowSpecialMove.posX && allowSpecialMove.posY) {
        moveVector->append(allowSpecialMove);
    }
}

bool PawnModel::ValidateMove(int x, int y) {
    auto pwnX = int{pwnBPosition.posX};
    auto pwnY = int{pwnBPosition.posY};
    if (isWhite) {
        if (std::abs(x - pwnX) == 1 && y - pwnY == 1) {
            return true;
        }
    } else {
        if (std::abs(x - pwnX) == 1 && y - pwnY == -1) {
            return true;
        }
    }
    return false;
}

auto PawnModel::CleanUp() -> bool {
    if (isFirstMove) {
        isFirstMove = false;
        return true;
    }
    if (pwnBPosition.posY == 0 || pwnBPosition.posY == 7) {
        isUpgradable = true;
    }
    return false;
}


