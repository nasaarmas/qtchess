#include <QApplication>
#include "headers/chessboard.h"
#include "headers/bishopmodel.h"
#include "headers/boardposition.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChessBoard chessboard;

    chessboard.show();
    return QApplication::exec();
}
