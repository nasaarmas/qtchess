//
// Created by Bartek on 9/9/2023.
//

#ifndef QTCHESS_PJC_CHESSBOARD_H
#define QTCHESS_PJC_CHESSBOARD_H

#include <QWidget>
#include <QAbstractGraphicsShapeItem>
#include "pawnmodel.h"

class ChessBoard : public QWidget
{
Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    void printPawn(PawnModel* pawn);
    ~ChessBoard() override;

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    PawnModel *pPawnToBeDrawn;
    // Define any private variables or methods you may need.
};

#endif //QTCHESS_PJC_CHESSBOARD_H
