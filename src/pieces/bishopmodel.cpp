#include <utility>
#include <QList>

#include "../../headers/pieces/bishopmodel.h"

BishopModel::BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite) {};

auto BishopModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void {
    auto breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX + i <= 7 && pwnBPosition.posY + i <= 7) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX + i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY + i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                                            static_cast<quint8>(pwnBPosition.posY + i)});
                    }
                    breakOuterLoop = true;
                    break;
                }
            }
        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                            static_cast<quint8>(pwnBPosition.posY + i)});
    }

    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX + i <= 7 && pwnBPosition.posY >= i) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX + i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY - i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                                            static_cast<quint8>(pwnBPosition.posY - i)});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }

        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                            static_cast<quint8>(pwnBPosition.posY - i)});
    }

    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX >= i && pwnBPosition.posY >= i) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX - i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY - i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                                            static_cast<quint8>(pwnBPosition.posY - i)});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }

        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                            static_cast<quint8>(pwnBPosition.posY - i)});
    }
    breakOuterLoop = false;
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX >= i && pwnBPosition.posY + i <= 7) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX - i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY + i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                                            static_cast<quint8>(pwnBPosition.posY + i)});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }

        } else {
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                            static_cast<quint8>(pwnBPosition.posY + i)});
    }

}

auto BishopModel::CleanUp() -> bool {
    return false;
}

auto BishopModel::ValidateMove(int x, int y) -> bool {
    return (std::abs(x - int{pwnBPosition.posX}) == std::abs(y - int{pwnBPosition.posY}));
}
