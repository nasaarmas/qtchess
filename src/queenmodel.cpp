#include <utility>

#include "../headers/queenmodel.h"


QueenModel::QueenModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite, isAlive) {};

void QueenModel::movePiece() {

}