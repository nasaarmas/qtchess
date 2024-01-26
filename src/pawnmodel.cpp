#include "../headers/pawnmodel.h"
#include <QDebug>
#include <utility>

PawnModel::PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite, bool isAlive) :
        pwnBPosition(pwnBPosition), imagePath(std::move(imagePath)), isWhite(isWhite), isAlive(isAlive) {}

void PawnModel::movePiece() {

}