#include <utility>

#include "../headers/rookmodel.h"


RookModel::RookModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite) {};

auto RookModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *>& pieces) -> void {
    auto breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posY + i <= 7) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY + i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({pwnBPosition.posX,
                                            static_cast<quint8>(pwnBPosition.posY + i)});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }
        }
        else{
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({pwnBPosition.posX,
                            static_cast<quint8>(pwnBPosition.posY + i)});
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX + i <= 7) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX + i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                                            pwnBPosition.posY});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }
        }
        else{
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX + i),
                            pwnBPosition.posY});
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posY >= i) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY - i == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({pwnBPosition.posX,
                                            static_cast<quint8>(pwnBPosition.posY - i)});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }
        }
        else{
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({pwnBPosition.posX,
                            static_cast<quint8>(pwnBPosition.posY - i)});
    }

    breakOuterLoop = bool{false};
    for (auto i = quint8{1}; i < 8; i++) {
        if (pwnBPosition.posX >= i) {
            for (const auto &pawn: pieces) {
                if (pwnBPosition.posX - i == pawn->pwnBPosition.posX &&
                    pwnBPosition.posY == pawn->pwnBPosition.posY) {
                    if (isWhite != pawn->isWhite) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                                            pwnBPosition.posY});
                    }
                    breakOuterLoop = true;
                    break;

                }
            }
        }
        else{
            break;
        }
        if (breakOuterLoop) {
            break;
        }
        moveVector->append({static_cast<quint8>(pwnBPosition.posX - i),
                            pwnBPosition.posY});
    }
}

auto RookModel::ValidateMove(int x, int y) -> bool {
    return x == int{pwnBPosition.posX} || y == int{pwnBPosition.posY};
}

auto RookModel::CleanUp() -> bool {
    return false;
}
