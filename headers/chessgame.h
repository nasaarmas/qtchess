#ifndef QTCHESS_PJC_CHESSGAME_H
#define QTCHESS_PJC_CHESSGAME_H

#include "chessboard.h"
#include "chessmodel.h"
#include "chessboard.h"

class ChessGame {
public:
    ChessGame();
    void showGame();

private:
    std::unique_ptr<ChessModel> pChessModel;
    std::unique_ptr<ChessBoard> pChessBoard;
};

#endif //QTCHESS_PJC_CHESSGAME_H
