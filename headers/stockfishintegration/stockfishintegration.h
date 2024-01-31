#ifndef QTCHESS_PJC_STOCKFISHINTEGRATION_H
#define QTCHESS_PJC_STOCKFISHINTEGRATION_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <array>
#include <memory>
#include <QProcess>
#include <QDebug>

class StockFishIntegration {
public:
    explicit StockFishIntegration(const QString &enginePath);

    auto getOutput(int waitTime) -> QString;

    auto testBestMove(const QString &fen, unsigned int waitTime) -> QString;

    ~StockFishIntegration();

private:
    auto sendCommand(const QString &command) -> void;

    QProcess stockfishProcess;
    QString enginePath;
};

#endif //QTCHESS_PJC_STOCKFISHINTEGRATION_H
