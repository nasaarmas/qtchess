#include <utility>

#include "../headers/knightmodel.h"


KnightModel::KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite, isAlive) {};

void KnightModel::movePiece() {

}