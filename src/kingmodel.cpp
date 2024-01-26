#include <utility>

#include "../headers/kingmodel.h"


KingModel::KingModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite, isAlive) {};

void KingModel::movePiece() {

}