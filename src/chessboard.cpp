#include "../headers/chessboard.h"
#include "../headers/chessgame.h"
#include <QPainter>
#include <QApplication>
#include <QBrush>
#include <utility>


ChessBoard::ChessBoard(QWidget *parent, int fontSize, int lftBrdPadding, int topBrdPadding, int cellSize) : QWidget(
        parent), fontSize(fontSize) {
    setFixedSize(1300, 700);
    this->fontSize = fontSize;
    this->lftBrdPadding = lftBrdPadding;
    this->topBrdPadding = topBrdPadding;
    this->cellSize = cellSize;

    moveCircles = {};

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
            auto columnNumberPlace = int{row * cellSize + topBrdPadding + (cellSize + fontSize) / 2};
            if (row == col) {
                painter.drawText(lftBrdPadding - fontSize - 6, columnNumberPlace, QString::number(8 - row));
                painter.drawText(8 * cellSize + lftBrdPadding + 6, columnNumberPlace, QString::number(8 - row));
            }
        }
        auto rowLetterPlace = int{row * cellSize + lftBrdPadding + (cellSize - fontSize) / 2};
        painter.drawText(rowLetterPlace, topBrdPadding - 6, QChar(row + 65));
        painter.drawText(rowLetterPlace, 8 * cellSize + topBrdPadding + fontSize + 8, QChar(row + 65));
    }

    for (auto moveCell: moveCircles) {
        painter.setBrush(Qt::red);
        painter.drawEllipse(lftBrdPadding + cellSize * moveCell.posX + 3,
                            topBrdPadding + 350 - cellSize * moveCell.posY + 3, cellSize - 6, cellSize - 6);
    }

    for (auto *piece: pieces) {
        ChessBoard::printPawn(piece, painter);
    }
    auto whichWhiteDead{0}, whichBlackDead{0};
    for (auto *piece: deadPiecesToDraw) {
        auto pawnToBeDrawn = QPixmap{QString(piece->imagePath)};
        auto pawnSize = int{60};
        pawnToBeDrawn = pawnToBeDrawn.scaled(pawnSize, pawnSize);
        if(piece->isWhite) {
            painter.drawPixmap(lftBrdPadding + cellSize * whichWhiteDead, topBrdPadding + 450, pawnToBeDrawn);
            whichWhiteDead++;
        }
        if(!piece->isWhite) {
            painter.drawPixmap(lftBrdPadding + cellSize * whichBlackDead, 50, pawnToBeDrawn);
            whichBlackDead++;
        }
    }

    auto clickableBlock = QRect(800, 250, 150, 50);
    painter.fillRect(clickableBlock, QColor(110, 46, 19));
    painter.setPen(Qt::white);
    painter.drawText(clickableBlock, Qt::AlignCenter, "Click me!");
}

void ChessBoard::printPawn(PawnModel *pawn, QPainter &painter) {
    //auto lftBrdPadding{195}, topBrdPadding{144};
    auto pawnToBeDrawn = QPixmap{QString(pawn->imagePath)};
    auto pawnSize = int{60};
    pawnToBeDrawn = pawnToBeDrawn.scaled(pawnSize, pawnSize);
    painter.drawPixmap(195 + 50 * (pawn->pwnBPosition.posX),
                       144 + 350 - 50 * (pawn->pwnBPosition.posY), pawnToBeDrawn);
}


void ChessBoard::mousePressEvent(QMouseEvent *event) {
    emit mouseClicked(event->x(), event->y());
}


ChessBoard::~ChessBoard() {
    pieces.clear();
    deadPiecesToDraw.clear();
}

void ChessBoard::setCurrentPieces(QList<PawnModel *> currentPieces, QList<PawnModel *> deadPieces) {
    pieces = std::move(currentPieces);
    deadPiecesToDraw = std::move(deadPieces);
}

void ChessBoard::updateCircles(QVector<BoardPosition> currentCircles) {
    moveCircles = std::move(currentCircles);
}




