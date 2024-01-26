#include "../headers/chessboard.h"

#include <QPainter>
#include <QApplication>
#include <QBrush>
#include <utility>



ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent) {
    setFixedSize(1300, 700);
    fontSize = 14;
    lftBrdPadding = 200;
    topBrdPadding = 150;
    cellSize = 50;

}

void ChessBoard::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor{44, 75, 107});


    painter.setFont(QFont("Times New Roman", fontSize));
    auto lightColor = QColor{146, 172, 172};
    auto darkColor = QColor{115, 115, 115};

    for (auto row{0}; row < 8; row++) {
        for (auto col{0}; col < 8; col++) {
            auto cellRect = QRect{col * cellSize + lftBrdPadding, row * cellSize + topBrdPadding, cellSize, cellSize};
            painter.fillRect(cellRect, (row + col) % 2 == 0 ? lightColor : darkColor);

            painter.setPen(Qt::black);
            painter.drawRect(cellRect);
            painter.setPen(Qt::white);
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

    for (auto *piece: pieces) {
        if (piece != nullptr) {
            ChessBoard::printPawn(piece, painter);
        }
    }

    auto clickableBlock = QRect(800, 250, 150, 50);
    painter.fillRect(clickableBlock, QColor(110, 46, 19));  // Red color, you can change it

    // Draw text inside the clickable block
    painter.setPen(Qt::white);
    painter.drawText(clickableBlock, Qt::AlignCenter, "Click me!");


}

void ChessBoard::printPawn(PawnModel *pawn, QPainter &painter) {
    //auto lftBrdPadding{195}, topBrdPadding{144};
    auto pawnToBeDrawn = QPixmap{QString(pawn->imagePath)};
    auto pawnSize{60};
    pawnToBeDrawn = pawnToBeDrawn.scaled(pawnSize, pawnSize);
    painter.drawPixmap(195 + 50 * (pawn->pwnBPosition.posX - 1),
                       144 + 400 - 50 * (pawn->pwnBPosition.posY), pawnToBeDrawn);
}

ChessBoard::~ChessBoard() {
    for (PawnModel *piece: this->pieces) {
        delete piece;
    }
    // Clear the list
    pieces.clear();
}


void ChessBoard::updatePieces(QList<PawnModel *> currentPieces) {
    pieces = std::move(currentPieces);
}

