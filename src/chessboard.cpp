//
// Created by Bartek on 9/9/2023.
//

#include "../headers/chessboard.h"
#include "../headers/pawnmodel.h"
#include <QPainter>
#include <QApplication>
#include <QBrush>


ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent) {
    setFixedSize(1300, 700);
    pPawnToBeDrawn = nullptr;
    // Initialize any variables or setup required for your chessboard.
}

void ChessBoard::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    // Create a QPainter to draw on the widget.
    QPainter painter(this);
    painter.fillRect(rect(), QColor(55, 51, 63));

    int fontSize = 14, lftBrdPadding = 200, topBrdPadding = 150, cellSize = 50;
    painter.setFont(QFont("Times New Roman", fontSize));
    painter.setPen(QColor(Qt::white));
    QColor lightColor(198, 179, 138);
    QColor darkColor(164, 125, 87);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QRect cellRect(col * cellSize + lftBrdPadding, row * cellSize + topBrdPadding, cellSize, cellSize);
            painter.fillRect(cellRect, (row + col) % 2 == 0 ? lightColor : darkColor);
            if (row == col) {
                painter.drawText(lftBrdPadding - fontSize - 6,
                                 row * cellSize + topBrdPadding + (cellSize + fontSize) / 2, QString::number(8 - row));
                painter.drawText(8 * cellSize + lftBrdPadding + 6,
                                 row * cellSize + topBrdPadding + (cellSize + fontSize) / 2, QString::number(8 - row));
            }
        }
        painter.drawText(row * cellSize + lftBrdPadding + (cellSize - fontSize) / 2, topBrdPadding - 6,
                         QChar(row + 65));
        painter.drawText(row * cellSize + lftBrdPadding + (cellSize - fontSize) / 2,
                         8 * cellSize + topBrdPadding + fontSize + 8,
                         QChar(row + 65));
    }


    QPixmap pawnBlack(":/pieces-png/black-pawn.png"); // Replace with your file path
    int pawnSize = 50;
    pawnBlack = pawnBlack.scaled(pawnSize, pawnSize);
    painter.drawPixmap(200, 200, pawnBlack);

    if (this->pPawnToBeDrawn != nullptr) {

        QPixmap pawnWhite(QString(":/" + this->pPawnToBeDrawn->imagePath)); // Replace with your file path
        pawnWhite = pawnWhite.scaled(pawnSize, pawnSize);
        painter.drawPixmap(lftBrdPadding + 50 * (this->pPawnToBeDrawn->pwnBPosition.posX - 1),
                           topBrdPadding + 50 * (this->pPawnToBeDrawn->pwnBPosition.posY - 1), pawnWhite);
        delete pPawnToBeDrawn;
        pPawnToBeDrawn = nullptr;

    }
}

void ChessBoard::printPawn(PawnModel *pawn) {
    this->pPawnToBeDrawn = new PawnModel(*pawn);
    update();
}

ChessBoard::~ChessBoard(){
    delete pPawnToBeDrawn;
}

