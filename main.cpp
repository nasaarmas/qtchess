#include <QApplication>
#include "headers/chessboard.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChessBoard chessboard;

    chessboard.show();

    return QApplication::exec();
}
