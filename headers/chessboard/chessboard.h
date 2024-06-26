#ifndef QTCHESS_PJC_CHESSBOARD_H
#define QTCHESS_PJC_CHESSBOARD_H

#include <QWidget>
#include <QAbstractGraphicsShapeItem>
#include "../pieces/pawnmodel.h"
#include "../boardposition.h"
#include <QList>
#include <QMouseEvent>

class ChessBoard : public QWidget {
Q_OBJECT

signals:

    void mouseClicked(int x, int y);

public:
    explicit ChessBoard(QWidget *parent = nullptr, int fontSize = 14, int lftBrdPadding = 200, int topBrdPadding = 150,
                        int cellSize = 50);

    auto setCurrentPieces(QList<PawnModel *> currentPieces, QList<PawnModel *> deadPieces) -> void;

    auto updateCircles(QVector<BoardPosition> currentCircles) -> void;

    auto updateStockfishMoves(QList<BoardPosition> currentStockfishMoves) -> void;

    static auto exitGame() -> void;

    auto setInfoString(QString newInfo) -> void;

    ~ChessBoard() override;

    QRect startGameButton;
    QRect exitButton;


protected:
    auto paintEvent(QPaintEvent *event) -> void override;

    auto mouseMoveEvent(QMouseEvent *event) -> void override;

    auto enterEvent(QEvent *event) -> void override;

    auto leaveEvent(QEvent *event) -> void override;

    auto mousePressEvent(QMouseEvent *event) -> void override;

private:
    static auto printPawn(PawnModel *pawn, QPainter &painter) -> void;

    QString infoText;
    QList<PawnModel *> pieces;
    QList<PawnModel *> deadPiecesToDraw;
    QVector<BoardPosition> moveCircles;
    QList<BoardPosition> stockfishMoves;
    int fontSize, lftBrdPadding, topBrdPadding, cellSize;
    bool isHoveringStartGameButton;
    bool isHoveringExitButton;
};

#endif //QTCHESS_PJC_CHESSBOARD_H
