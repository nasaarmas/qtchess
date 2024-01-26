#include <utility>

#include "../headers/bishopmodel.h"

BishopModel::BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) : PawnModel(
        pwnBPosition, std::move(imagePath), isWhite, isAlive) {};

void BishopModel::movePiece() {

}