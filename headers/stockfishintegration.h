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

    ~StockFishIntegration();

    void sendCommand(const std::string &command);

    std::string getOutput(unsigned int waitTime);

    std::string testBestMove(const std::string &fen, unsigned int waitTime);

private:
    QProcess stockfishProcess;
    QString enginePath;


};

#endif //QTCHESS_PJC_STOCKFISHINTEGRATION_H
