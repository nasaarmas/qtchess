#ifndef QTCHESS_PJC_CHESSBOARD_H
#define QTCHESS_PJC_CHESSBOARD_H

#include <QWidget>
#include <QAbstractGraphicsShapeItem>
#include "pawnmodel.h"
#include "bishopmodel.h"
#include "rookmodel.h"
#include "knightmodel.h"
#include "queenmodel.h"
#include "kingmodel.h"
#include <QList>
class ChessBoard : public QWidget
{
Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);
    static void printPawn(PawnModel* pawn, QPainter& painter);
    static void initializePieces(QList<PawnModel *>& allPieces);
    QList<PawnModel*> pieces;
    ~ChessBoard() override;

protected:
    void paintEvent(QPaintEvent *event) override;


private:
    //PawnModel *pPawnToBeDrawn;
    // Define any private variables or methods you may need.
};

#endif //QTCHESS_PJC_CHESSBOARD_H
