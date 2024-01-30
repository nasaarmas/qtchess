/**
 * @file chessgame.h
 * @brief Definition of the ChessGame class, which manages the interaction between the chess model and the user interface.
 */

#ifndef QTCHESS_PJC_CHESSGAME_H
#define QTCHESS_PJC_CHESSGAME_H

#include "chessboard.h"
#include "chessmodel.h"
#include <QObject>
#include "stockfishintegration.h"

/**
 * @class ChessGame
 * @brief Orchestrates a game of chess, handling user interactions and managing the game state.
 *
 * This class acts as a mediator between the chess model, the chessboard view, and the StockFish engine.
 * It processes user mouse clicks to move chess pieces and manages the overall game flow.
 */
class ChessGame : public QObject {
Q_OBJECT;
public:
    explicit ChessGame(QObject *parent = nullptr); ///< Constructor initializes the chess game with a parent if provided.

    auto showGame() -> void; ///< Displays the chess game board.

public slots:
    void processMouseClick(int x, int y); ///< Processes mouse clicks on the chess board.

private:
    std::unique_ptr<ChessModel> pChessModel; ///< Pointer to the chess model managing the game logic.
    std::unique_ptr<ChessBoard> pChessBoard; ///< Pointer to the chess board UI.
    std::unique_ptr<StockFishIntegration> pStockFish; ///< Pointer to the StockFish chess engine integration.
};

#endif //QTCHESS_PJC_CHESSGAME_H
