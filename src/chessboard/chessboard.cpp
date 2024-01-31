#include "../../headers/chessboard/chessboard.h"
#include "../../headers/chessgame/chessgame.h"
#include <QPainter>
#include <QApplication>
#include <QBrush>
#include <utility>


ChessBoard::ChessBoard(QWidget *parent, int fontSize, int lftBrdPadding, int topBrdPadding, int cellSize) : QWidget(
        parent), fontSize(fontSize) {
    this->setFixedSize(1300, 700);
    this->fontSize = fontSize;
    this->lftBrdPadding = lftBrdPadding;
    this->topBrdPadding = topBrdPadding;
    this->cellSize = cellSize;
    setMouseTracking(true);
    isHoveringStartGameButton = false;
    isHoveringExitButton = false;
    moveCircles = {};
    infoText = "Welcome to my chess! \nClick start to start game";

}

auto ChessBoard::setCurrentPieces(QList<PawnModel *> currentPieces, QList<PawnModel *> deadPieces) -> void {
    pieces = std::move(currentPieces);
    deadPiecesToDraw = std::move(deadPieces);
}

auto ChessBoard::updateCircles(QVector<BoardPosition> currentCircles) -> void {
    moveCircles = std::move(currentCircles);
}

auto ChessBoard::exitGame() -> void {
    QApplication::quit();
}

auto ChessBoard::paintEvent(QPaintEvent *) -> void {
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
        if (piece->isWhite) {
            painter.drawPixmap(lftBrdPadding + cellSize * whichWhiteDead, topBrdPadding + 450, pawnToBeDrawn);
            whichWhiteDead++;
        }
        if (!piece->isWhite) {
            painter.drawPixmap(lftBrdPadding + cellSize * whichBlackDead, 50, pawnToBeDrawn);
            whichBlackDead++;
        }
    }

    startGameButton = QRect(800, 250, 150, 50);
    QColor blockColor = isHoveringStartGameButton ? QColor(150, 75, 0) : QColor(110, 46, 19);
    painter.fillRect(startGameButton, blockColor);
    painter.setPen(Qt::white);
    painter.drawText(startGameButton, Qt::AlignCenter, "(Re)Start Game");

    exitButton = QRect(800, 350, 150, 50);
    QColor exitButtonColor = isHoveringExitButton ? QColor(150, 75, 0) : QColor(110, 46, 19);
    painter.fillRect(exitButton, exitButtonColor);
    painter.setPen(Qt::white);
    painter.drawText(exitButton, Qt::AlignCenter, "Exit");

    QFont bigFont("Times New Roman", 20);  // Change "Arial" to your preferred font and "20" to your desired size
    painter.setFont(bigFont);
    painter.setPen(Qt::white);  // Set the text color to white

// Define QRects for the bigger text above the buttons
    QRect startGameTextRect(startGameButton.x() - 50, startGameButton.y() - 100, startGameButton.width() * 2 + 50, 100);

// Draw the text
    painter.drawText(startGameTextRect, Qt::AlignCenter, infoText);
    painter.setFont(QFont("Times New Roman", fontSize));
}

auto ChessBoard::mouseMoveEvent(QMouseEvent *event) -> void {
    // Check if the mouse is over the startGameButton
    if (startGameButton.contains(event->pos())) {
        if (!isHoveringStartGameButton) {
            isHoveringStartGameButton = true;
            update(startGameButton);  // Repaint just the startGameButton area
        }
    } else {
        if (isHoveringStartGameButton) {
            isHoveringStartGameButton = false;
            update(startGameButton);  // Repaint just the startGameButton area
        }
    }
    if (exitButton.contains(event->pos())) {
        if (!isHoveringExitButton) {
            isHoveringExitButton = true;
            update(exitButton);  // Repaint just the startGameButton area
        }
    } else {
        if (isHoveringExitButton) {
            isHoveringExitButton = false;
            update(exitButton);  // Repaint just the startGameButton area
        }
    }
}

auto ChessBoard::enterEvent(QEvent *event) -> void {
    // Reset hover state when the cursor enters the widget
    isHoveringStartGameButton = false;
    isHoveringExitButton = false;
    QWidget::enterEvent(event);
}

auto ChessBoard::leaveEvent(QEvent *event) -> void {
    // Reset hover state when the cursor leaves the widget
    if (isHoveringStartGameButton) {
        isHoveringStartGameButton = false;
        update(startGameButton);  // Repaint just the startGameButton area
    } else if (isHoveringExitButton) {
        isHoveringExitButton = false;
        update(exitButton);  // Repaint just the startGameButton area
    }
    QWidget::leaveEvent(event);
}

auto ChessBoard::mousePressEvent(QMouseEvent *event) -> void {
    emit mouseClicked(event->x(), event->y());
}

auto ChessBoard::printPawn(PawnModel *pawn, QPainter &painter) -> void {
    auto pawnToBeDrawn = QPixmap{QString(pawn->imagePath)};
    auto pawnSize = int{60};
    pawnToBeDrawn = pawnToBeDrawn.scaled(pawnSize, pawnSize);
    painter.drawPixmap(195 + 50 * (pawn->pwnBPosition.posX),
                       144 + 350 - 50 * (pawn->pwnBPosition.posY), pawnToBeDrawn);
}

ChessBoard::~ChessBoard() {
    pieces.clear();
    deadPiecesToDraw.clear();
}

auto ChessBoard::setInfoString(QString newInfo) -> void {
    infoText = std::move(newInfo);
}



