//
// Created by Bartek on 9/9/2023.
//

#include "../headers/chessboard.h"
#include <QPainter>
#include <QApplication>
#include <QBrush>


ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    setFixedSize(1300, 700);
    // Initialize any variables or setup required for your chessboard.
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // Create a QPainter to draw on the widget.
    QPainter painter(this);
    painter.fillRect(rect(),  QColor(55, 51, 63));
    // Set up the chessboard drawing parameters.
    int cellSize = 50; // Adjust the cell size as needed.
    QColor lightColor(198, 179, 138);
    QColor darkColor(164, 125, 87);
    // Loop through rows and columns to draw the chessboard pattern.
    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            QRect cellRect(col * cellSize + 200, row * cellSize + 150, cellSize, cellSize);
            painter.fillRect(cellRect, (row + col) % 2 == 0 ? lightColor : darkColor);
        }
    }

    QPixmap pawnWhite(":/pieces-png/white-pawn.png"); // Replace with your file path
    QPixmap pawnBlack(":/pieces-png/black-pawn.png"); // Replace with your file path

    // Resize the pawn images (adjust the size as needed)
    int pawnSize = 50;
    pawnWhite = pawnWhite.scaled(pawnSize, pawnSize);
    pawnBlack = pawnBlack.scaled(pawnSize, pawnSize);

    // Draw the resized pawn images at specific positions
    // For example, drawing a white pawn at (100, 100)
    painter.drawPixmap(100, 100, pawnWhite);
    painter.drawPixmap(200, 200, pawnBlack);
}

void ChessBoard::printPawns() {

}
