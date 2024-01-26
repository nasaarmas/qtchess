#include <utility>

#include "../headers/rookmodel.h"


RookModel::RookModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite, isAlive) {};

void RookModel::movePiece() {

}