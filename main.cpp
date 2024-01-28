#include <QApplication>
#include "headers/chessgame.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    auto chessGame = ChessGame{};

    chessGame.showGame();
    return QApplication::exec();
}
