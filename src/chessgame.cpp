#include "../headers/chessgame.h"
#include "QDebug"


ChessGame::ChessGame(QObject *parent) : pChessModel(std::make_unique<ChessModel>()),
                                        pChessBoard(std::make_unique<ChessBoard>()) {
    pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
    QObject::connect(pChessBoard.get(), &ChessBoard::mouseClicked, this, &ChessGame::processMouseClick);
}

auto ChessGame::processMouseClick(int x, int y) -> void {

    auto lftPad{pChessModel->getLftPadding()};
    auto topPad{pChessModel->getTopPadding()};
    auto cellSize{pChessModel->getCellSize()};

    if (x > lftPad && x < 8 * cellSize + lftPad && y > topPad && y < 8 * cellSize + topPad && pChessModel->GameOn()) {
        auto column = static_cast<quint8>((x - lftPad) / cellSize);
        auto row = static_cast<quint8>(7 - ((y - topPad) / cellSize));

        if (!pChessModel->isPieceSelected()) {
            pChessModel->getPieceClicked(column, row);
            pChessBoard->updateCircles(pChessModel->getMovesVector());
            pChessBoard->update();
        } else {
            pChessModel->ChangePiecePlace(column, row);
            pChessBoard->updateCircles(pChessModel->getMovesVector());
            pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
            pChessBoard->update();
        }
    }
    if (pChessBoard->startGameButton.contains(x, y)) {
        pChessModel.reset();
        pChessModel = std::make_unique<ChessModel>();
        pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
        pChessModel->startGame();
        pChessBoard->update();
    }
    if (pChessBoard->exitButton.contains(x, y)) {
        pChessBoard->exitGame();
    }
    if (pChessModel->isMate()) {
        qDebug() << "Biale 123wygrywaja \n";
    }
}

auto ChessGame::showGame() -> void {
    pChessBoard->show();
}