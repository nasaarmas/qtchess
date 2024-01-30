#include "../headers/stockfishintegration.h"


StockFishIntegration::StockFishIntegration(const QString &enginePath) {
    stockfishProcess.start(enginePath, QProcess::ReadWrite);
    if (!stockfishProcess.waitForStarted()) {
        qDebug() << "Stockfish failed to start." << Qt::endl;
    } else {
        sendCommand("uci\n");  // Initialize the UCI (Universal Chess Interface)
    }
}

StockFishIntegration::~StockFishIntegration() {
    sendCommand("quit");
    stockfishProcess.waitForFinished();
    stockfishProcess.close();
}

void StockFishIntegration::sendCommand(const std::string &command) {
    if (stockfishProcess.state() == QProcess::Running) {
        stockfishProcess.write((command + "\n").c_str());
    }
}

std::string StockFishIntegration::getOutput(unsigned int waitTime) {
    std::string output;
    if (stockfishProcess.waitForReadyRead(waitTime)) {
        output = stockfishProcess.readAllStandardOutput().toStdString();
    }
    return output;
}

std::string StockFishIntegration::testBestMove(const std::string &fen, unsigned int waitTime) {
    // Reset the engine to a new game and set the position
    sendCommand("ucinewgame");
    sendCommand("position fen " + fen);

    // Ask the engine to calculate the best move
    sendCommand("go depth 10");

    // Read the output from the engine
    std::string output;
    std::string bestMoveLine;
    do {
        output = getOutput(waitTime);
        //qDebug() << "Output: " << QString::fromStdString(output) << Qt::endl; // Add this line for debugging
        if (output.find("bestmove") != std::string::npos) {
            bestMoveLine = output;
            break;
        }
    } while (!output.empty());


    // Extract the best move from the line
    std::string bestMove;
    if (!bestMoveLine.empty()) {
        size_t startPos = bestMoveLine.find("bestmove");
        if (startPos != std::string::npos) {
            startPos += 9; // "bestmove" length + 1 for space
            size_t endPos = bestMoveLine.find(" ", startPos);
            bestMove = bestMoveLine.substr(startPos, endPos - startPos);
        }
    }

    return bestMove;
}
