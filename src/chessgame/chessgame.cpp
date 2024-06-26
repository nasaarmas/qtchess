#include "../../headers/chessgame/chessgame.h"
#include "QDebug"


ChessGame::ChessGame(QObject *parent) : pChessModel(std::make_unique<ChessModel>()),
                                        pChessBoard(std::make_unique<ChessBoard>()) {
    pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
    QObject::connect(pChessBoard.get(), &ChessBoard::mouseClicked, this, &ChessGame::processMouseClick);
    pStockFish = std::make_unique<StockFishIntegration>("../src/stockfishintegration/stockfish.exe");
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
            pChessModel->popCurrentPieceFromMoves();
        } else {
            pChessModel->ChangePiecePlace(column, row);
            pChessBoard->updateCircles(pChessModel->getMovesVector());
            pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
            pChessBoard->update();
            pChessModel->popCurrentPieceFromMoves();
        }
        pChessBoard->setInfoString((pChessModel->isWhiteTurn() ? "White player turn" : "Black player turn"));
        if (pChessModel->isMate()) {
            if (pChessModel->isKingAttacked()) {
                pChessBoard->setInfoString((pChessModel->isWhiteTurn() ? "Black WINS!" : "White WINS!"));
            } else {
                pChessBoard->setInfoString(("DRAW - stalmate!"));
            }
            pChessModel->stopGame();
            pChessBoard->update();
        }
    }
    if (pChessBoard->startGameButton.contains(x, y)) {
        pChessModel.reset();
        pChessModel = std::make_unique<ChessModel>();
        pChessBoard->setCurrentPieces(pChessModel->getCurrentPieces(), pChessModel->getDeadPieces());
        pChessBoard->updateCircles(pChessModel->getMovesVector());
        pChessModel->startGame();
        pChessBoard->setInfoString("White player turn");
        pChessBoard->update();
    }
    if (pChessBoard->exitButton.contains(x, y)) {
        pChessBoard->exitGame();
    }
    qDebug() << pChessModel->generateFEN() << Qt::endl;
    QString bestMove = pStockFish->testBestMove(pChessModel->generateFEN(), 1000); // waitTime in milliseconds
    qDebug() << "Best move: " << bestMove << Qt::endl;
    pChessBoard->updateStockfishMoves(pStockFish->TranslateToBoardPos(bestMove));
}

auto ChessGame::showGame() -> void {
    pChessBoard->show();
}