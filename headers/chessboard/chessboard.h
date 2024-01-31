/**
 * @file chessboard.h
 * @brief Definition of the ChessBoard class, which represents the visual representation of the chessboard.
 */

#ifndef QTCHESS_PJC_CHESSBOARD_H
#define QTCHESS_PJC_CHESSBOARD_H

#include <QWidget>
#include <QAbstractGraphicsShapeItem>
#include "../pieces/pawnmodel.h"
#include "../boardposition.h"
#include <QList>
#include <QMouseEvent>

/**
 * @class ChessBoard
 * @brief Represents the visual display of the chessboard, handling rendering and user interaction.
 *
 * This class is responsible for drawing the chessboard, the pieces on it, and handling user mouse events.
 * It communicates with the ChessGame class to notify about mouse clicks and updates the display based on game state.
 */
class ChessBoard : public QWidget {
Q_OBJECT

signals:
    void mouseClicked(int x, int y); ///< Signal emitted when the mouse is clicked on the board.

public:
    explicit ChessBoard(QWidget *parent = nullptr, int fontSize = 14, int lftBrdPadding = 200, int topBrdPadding = 150,
                        int cellSize = 50); ///< Constructor initializes the chessboard with given parameters.

    auto setCurrentPieces(QList<PawnModel *> currentPieces, QList<PawnModel *> deadPieces) -> void; ///< Updates the current and dead pieces on the board.

    auto updateCircles(QVector<BoardPosition> currentCircles) -> void; ///< Updates the move circles indicating possible moves.

    static auto exitGame() -> void; ///< Triggers the exit game routine.

    auto setInfoString(QString newInfo) -> void; ///< Sets the information string to display on the board.

    ~ChessBoard() override; ///< Destructor.

    QRect startGameButton; ///< Rectangle area for the start game button.
    QRect exitButton; ///< Rectangle area for the exit game button.
    bool isHoveringStartGameButton; ///< Indicates if the mouse is hovering over the start game button.
    bool isHoveringExitButton; ///< Indicates if the mouse is hovering over the exit game button.

protected:
    auto paintEvent(QPaintEvent *event) -> void override; ///< Handles the paint event to draw the board and pieces.

    auto mouseMoveEvent(QMouseEvent *event) -> void override; ///< Handles mouse move events.

    auto enterEvent(QEvent *event) -> void override; ///< Handles the enter event when the mouse enters the widget.

    auto leaveEvent(QEvent *event) -> void override; ///< Handles the leave event when the mouse leaves the widget.

    auto mousePressEvent(QMouseEvent *event) -> void override; ///< Handles mouse press events.

private:
    static auto printPawn(PawnModel *pawn, QPainter &painter) -> void; ///< Draws a pawn on the board.

    QString infoText; ///< Information text to display on the board.
    QList<PawnModel *> pieces; ///< List of current pieces on the board.
    QList<PawnModel *> deadPiecesToDraw; ///< List of dead pieces to draw on the side.
    QVector<BoardPosition> moveCircles; ///< Vector of board positions indicating possible moves.
    int fontSize, lftBrdPadding, topBrdPadding, cellSize; ///< Visual settings for the board.

};

#endif //QTCHESS_PJC_CHESSBOARD_H
