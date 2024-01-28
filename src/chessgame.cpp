#include "../headers/chessgame.h"
#include "QDebug"


ChessGame::ChessGame(QObject *parent) : pChessModel(std::make_unique<ChessModel>()),
                                        pChessBoard(std::make_unique<ChessBoard>()) {
    pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
    QObject::connect(pChessBoard.get(), &ChessBoard::mouseClicked, this, &ChessGame::processMouseClick);
}

void ChessGame::processMouseClick(int x, int y) {

    auto lftPad{pChessModel->getLftPadding()};
    auto topPad{pChessModel->getTopPadding()};
    auto cellSize{pChessModel->getCellSize()};

    if (x > lftPad && x < 8 * cellSize + lftPad && y > topPad && y < 8 * cellSize + topPad) {
        auto column = static_cast<quint8>((x - lftPad) / cellSize);
        auto row = static_cast<quint8>(7 - ((y - topPad) / cellSize));

        if (!pChessModel->IsPieceSelected()) {
            pChessModel->getPieceClicked(column, row);
            qDebug() << column << row << "piece: " ;//<< clickedPiece->isAlive << Qt::endl;
            pChessBoard->updateCircles(pChessModel->getMovesVector());
            pChessBoard->update();
        }
        else {
            pChessModel->ChangePiecePlace(column, row);
            pChessBoard->updateCircles(pChessModel->getMovesVector());
            pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
            pChessBoard->update();
        }
    }
    }

    void ChessGame::showGame() {
        pChessBoard->show();
    }