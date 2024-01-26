#include "../headers/pawnmodel.h"

PawnModel::PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) {
    this->pwnBPosition = pwnBPosition;
    this->imagePath = imagePath;
    this->isWhite = isWhite;
    this->isAlive = isAlive;
}

void PawnModel::movePiece() {

}