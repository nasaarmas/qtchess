#ifndef QTCHESS_PJC_CHESSBOARD_H
#define QTCHESS_PJC_CHESSBOARD_H

#include <QWidget>
#include <QAbstractGraphicsShapeItem>
#include "pawnmodel.h"
#include "boardposition.h"
#include <QList>
#include <QMouseEvent>

class ChessBoard : public QWidget {
Q_OBJECT

signals:

    void mouseClicked(int x, int y);

public:
    explicit ChessBoard(QWidget *parent = nullptr, int fontSize = 14, int lftBrdPadding = 200, int topBrdPadding = 150,
               int cellSize = 50);



    void setCurrentPieces(QList<PawnModel *> currentPieces, QList<PawnModel *> deadPieces);
    void updateCircles(QVector<BoardPosition> currentCircles);
    ~ChessBoard() override;


protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

private:
    static void printPawn(PawnModel *pawn, QPainter &painter);
    QList<PawnModel *> pieces;
    QList<PawnModel *> deadPiecesToDraw;
    QVector<BoardPosition> moveCircles;
    int fontSize, lftBrdPadding, topBrdPadding, cellSize;

};

#endif //QTCHESS_PJC_CHESSBOARD_H
