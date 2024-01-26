#include <QApplication>
#include "headers/chessboard.h"
#include "headers/bishopmodel.h"
#include "headers/boardposition.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ChessBoard chessboard;

    chessboard.show();
    BoardPosition bishopBrdPos{3, 1};
    auto *bishopPawn = new BishopModel(bishopBrdPos, "pieces-png/black-bishop.png");

    delete bishopPawn;
    return QApplication::exec();
}
