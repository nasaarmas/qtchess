#include "../../headers/stockfishintegration/stockfishintegration.h"

StockFishIntegration::StockFishIntegration(const QString &enginePath) {
    QStringList arguments;  // Create an empty QStringList for the arguments if there are any
    stockfishProcess.start(enginePath, arguments, QProcess::ReadWrite);  // Updated start function
    if (!stockfishProcess.waitForStarted()) {
        qDebug() << "Stockfish failed to start." << Qt::endl;
    } else {
        sendCommand("uci");  // Initialize the UCI (Universal Chess Interface)
    }
}


auto StockFishIntegration::getOutput(int waitTime) -> QString {
    QString output;
    if (stockfishProcess.waitForReadyRead(waitTime)) {
        output = stockfishProcess.readAllStandardOutput();
    }
    return output;
}

auto StockFishIntegration::testBestMove(const QString &fen, unsigned int waitTime) -> QString {
    // Reset the engine to a new game and set the position
    sendCommand("ucinewgame");
    sendCommand("position fen " + fen);

    // Ask the engine to calculate the best move
    sendCommand("go depth 15");

    // Read the output from the engine
    QString output;
    QString bestMoveLine;
    do {
        output = getOutput(waitTime);
        //qDebug() << "Output: " << output; // Add this line for debugging
        if (output.contains("bestmove")) {
            bestMoveLine = output;
            break;
        }
    } while (!output.isEmpty());

    // Extract the best move from the line
    QString bestMove;
    if (!bestMoveLine.isEmpty()) {
        int startPos = bestMoveLine.indexOf("bestmove") + 9; // "bestmove" length + 1 for space
        int endPos = bestMoveLine.indexOf(" ", startPos);
        bestMove = bestMoveLine.mid(startPos, endPos - startPos);
    }
    return bestMove;
}

StockFishIntegration::~StockFishIntegration() {
    sendCommand("quit");
    stockfishProcess.waitForFinished();
    stockfishProcess.close();
}

auto StockFishIntegration::sendCommand(const QString &command) -> void {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.write((command + "\n").toUtf8());
    }
}

auto StockFishIntegration::TranslateToBoardPos(const QString& suggestedMove) -> QList<BoardPosition> {
    if (suggestedMove.length() != 4) {
        // Invalid move format, handle error or return an empty list
        return QList<BoardPosition>{};
    }

    auto suggestedPiece = suggestedMove.left(2);
    auto suggestedMovePlace = suggestedMove.right(2);

    // Assuming chess board is 8x8
    quint8 column = suggestedPiece.at(0).toLatin1() - 'a';
    quint8 row = suggestedPiece.at(1).digitValue() - 1;

    auto suggestedMoveList = QList<BoardPosition>{};
    suggestedMoveList.append({column, row});
    column = suggestedMovePlace.at(0).toLatin1() - 'a';
    row = suggestedMovePlace.at(1).digitValue() - 1;
    suggestedMoveList.append({column, row});

    return suggestedMoveList;
}



