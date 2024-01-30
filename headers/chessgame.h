#ifndef QTCHESS_PJC_CHESSGAME_H
#define QTCHESS_PJC_CHESSGAME_H

#include "chessboard.h"
#include "chessmodel.h"
#include <QObject>
#include "stockfishintegration.h"

class ChessGame : public QObject {
Q_OBJECT;
public:
    explicit ChessGame(QObject *parent = nullptr);

    auto showGame() -> void;

public slots:
    void processMouseClick(int x, int y);

private:
    std::unique_ptr<ChessModel> pChessModel;
    std::unique_ptr<ChessBoard> pChessBoard;
    std::unique_ptr<StockFishIntegration> pStockFish;
};

#endif //QTCHESS_PJC_CHESSGAME_H
