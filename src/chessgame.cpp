#include "../headers/chessgame.h"

ChessGame::ChessGame() : pChessModel(std::make_unique<ChessModel>()), pChessBoard(std::make_unique<ChessBoard>()) {
    pChessBoard->updatePieces(pChessModel->getCurrentPieces());

}

void ChessGame::showGame() {
    pChessBoard->show();
}