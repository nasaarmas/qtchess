#include <utility>
#include "../headers/kingmodel.h"
#include <QDebug>


KingModel::KingModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite) {};

auto KingModel::PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void {
    if (pwnBPosition.posX >= 1) {
        moveVector->append({static_cast<quint8>(pwnBPosition.posX - 1), pwnBPosition.posY});
        if (pwnBPosition.posY + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 1), static_cast<quint8>(pwnBPosition.posY + 1)});
        }
        if (pwnBPosition.posY >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX - 1), static_cast<quint8>(pwnBPosition.posY - 1)});
        }
    }
    if (pwnBPosition.posX + 1 <= 7) {
        moveVector->append({static_cast<quint8>(pwnBPosition.posX + 1), pwnBPosition.posY});
        if (pwnBPosition.posY + 1 <= 7) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 1), static_cast<quint8>(pwnBPosition.posY + 1)});
        }
        if (pwnBPosition.posY >= 1) {
            moveVector->append(
                    {static_cast<quint8>(pwnBPosition.posX + 1), static_cast<quint8>(pwnBPosition.posY - 1)});
        }
    }
    if (pwnBPosition.posY >= 1) {
        moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY - 1)});
    }
    if (pwnBPosition.posY + 1 <= 7) {
        moveVector->append({pwnBPosition.posX, static_cast<quint8>(pwnBPosition.posY + 1)});
    }

    if (isFirstMove) {
        for (const auto &rook: pieces) {
            if (rook->imagePath == (isWhite ? ":/pieces-png/white-rook.png" : ":/pieces-png/black-rook.png")) {
                if (rook->isFirstMove) {
                    bool isPathClear = true;
                    int direction = (rook->pwnBPosition.posX > pwnBPosition.posX) ? 1 : -1;

                    // Check if squares between king and rook are empty
                    for (int offsetX = direction;
                         pwnBPosition.posX + offsetX != rook->pwnBPosition.posX; offsetX += direction) {
                        for (const auto &piece: pieces) {
                            if (piece->pwnBPosition.posX == pwnBPosition.posX + offsetX &&
                                piece->pwnBPosition.posY == pwnBPosition.posY) {
                                isPathClear = false;
                                break;
                            }
                        }
                        if (!isPathClear) {
                            break;
                        }
                    }

                    if (isPathClear) {
                        moveVector->append({static_cast<quint8>(pwnBPosition.posX + 2 * direction), pwnBPosition.posY});
                    }
                }
            }
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


    // Iterate through the moveVector to check if a castling move is present
    if (isFirstMove) { // Ensure the king has not moved
        for (const auto &move: *moveVector) {
            if (((move.posX == pwnBPosition.posX + 2) || // King moves two squares to the right
                 (move.posX == pwnBPosition.posX - 2)) && // King moves two squares to the left
                move.posY == pwnBPosition.posY) { // Y position remains the same

                this->allowSpecialMove = {20, 20};
                break;
            }
        }
    }


}

auto KingModel::ValidateMove(int x, int y) -> bool {
    return std::abs(x - int{pwnBPosition.posX}) <= 1 && std::abs(y - int{pwnBPosition.posY}) <= 1;
}

auto KingModel::CleanUp() -> bool {
    if (isFirstMove) {
        isFirstMove = false;
    }
    return false;
}
