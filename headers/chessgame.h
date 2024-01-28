#ifndef QTCHESS_PJC_CHESSGAME_H
#define QTCHESS_PJC_CHESSGAME_H

#include "chessboard.h"
#include "chessmodel.h"
#include <QObject>

class ChessGame : public QObject {
Q_OBJECT;
public:
    explicit ChessGame(QObject *parent = nullptr);
    void showGame();

public slots:
    void processMouseClick(int x, int y);

private:
    std::unique_ptr<ChessModel> pChessModel;
    std::unique_ptr<ChessBoard> pChessBoard;
};

#endif //QTCHESS_PJC_CHESSGAME_H
