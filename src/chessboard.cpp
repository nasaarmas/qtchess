#include "../headers/chessboard.h"

#include <QPainter>
#include <QApplication>
#include <QBrush>
//#include <QDebug>


ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent) {
    setFixedSize(1300, 700);
    initializePieces(this->pieces);

}

void ChessBoard::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(rect(), QColor{44, 75, 107});

    auto fontSize{14}, lftBrdPadding{200}, topBrdPadding{150}, cellSize{50};
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

    for (PawnModel *piece: pieces) {
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
    auto lftBrdPadding{195}, topBrdPadding{144};
    auto pawnToBeDrawn = QPixmap{QString(pawn->imagePath)};
    auto pawnSize{60};
    pawnToBeDrawn = pawnToBeDrawn.scaled(pawnSize, pawnSize);
    painter.drawPixmap(lftBrdPadding + 50 * (pawn->pwnBPosition.posX - 1),
                       topBrdPadding + 400 - 50 * (pawn->pwnBPosition.posY), pawnToBeDrawn);
}

ChessBoard::~ChessBoard() {
    for (PawnModel *piece: this->pieces) {
        delete piece;
    }
    // Clear the list
    pieces.clear();
}

void ChessBoard::initializePieces(QList<PawnModel *> &allPieces) {
    auto piecePosistion = BoardPosition{1, 1};
    auto rookWhite1 = new RookModel(piecePosistion, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite1);
    piecePosistion = {8, 1};
    auto rookWhite2 = new RookModel(piecePosistion, ":/pieces-png/white-rook.png");
    allPieces.append(rookWhite2);

    piecePosistion = {2, 1};
    auto knightWhite1 = new KnightModel(piecePosistion, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite1);
    piecePosistion = {7, 1};
    auto knightWhite2 = new KnightModel(piecePosistion, ":/pieces-png/white-knight.png");
    allPieces.append(knightWhite2);

    piecePosistion = {3, 1};
    auto bishopWhite1 = new BishopModel(piecePosistion, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite1);
    piecePosistion = {6, 1};
    auto bishopWhite2 = new BishopModel(piecePosistion, ":/pieces-png/white-bishop.png");
    allPieces.append(bishopWhite2);

    piecePosistion = {4, 1};
    auto queenWhite = new QueenModel(piecePosistion, ":/pieces-png/white-queen.png");
    allPieces.append(queenWhite);

    piecePosistion = {5, 1};
    auto kingWhite = new KingModel(piecePosistion, ":/pieces-png/white-king.png");
    allPieces.append(kingWhite);

    for (auto i = quint8{1}; i <= 8; i++) {
        piecePosistion = {i, 2};
        auto pawnPiece = new PawnModel(piecePosistion, ":/pieces-png/white-pawn.png");
        allPieces.append(pawnPiece);
    }


    piecePosistion = {1, 8};
    auto rookBlack1 = new RookModel(piecePosistion, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack1);
    piecePosistion = {8, 8};
    auto rookBlack2 = new RookModel(piecePosistion, ":/pieces-png/black-rook.png", false);
    allPieces.append(rookBlack2);

    piecePosistion = {2, 8};
    auto knightBlack1 = new KnightModel(piecePosistion, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack1);
    piecePosistion = {7, 8};
    auto knightBlack2 = new KnightModel(piecePosistion, ":/pieces-png/black-knight.png", false);
    allPieces.append(knightBlack2);

    piecePosistion = {3, 8};
    auto bishopBlack1 = new BishopModel(piecePosistion, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack1);
    piecePosistion = {6, 8};
    auto bishopBlack2 = new BishopModel(piecePosistion, ":/pieces-png/black-bishop.png", false);
    allPieces.append(bishopBlack2);

    piecePosistion = {4, 8};
    auto queenBlack = new QueenModel(piecePosistion, ":/pieces-png/black-queen.png", false);
    allPieces.append(queenBlack);

    piecePosistion = {5, 8};
    auto kingBlack = new KingModel(piecePosistion, ":/pieces-png/black-king.png");
    allPieces.append(kingBlack);

    for (auto i = quint8{1}; i <= 8; i++) {
        piecePosistion = {i, 7};
        auto pawnPiece = new PawnModel(piecePosistion, ":/pieces-png/black-pawn.png", false);
        allPieces.append(pawnPiece);
    }
}

