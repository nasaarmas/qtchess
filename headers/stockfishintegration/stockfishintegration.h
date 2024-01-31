/**
 * @file stockfishintegratiob.h
 * @brief Definition of the StockFishIntegration class, that represent connection with stockfish.
 */

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
/**
 * @class StockFishIntegration
 * @brief Integration class for the Stockfish chess engine.
 *
 * This class is responsible for managing the interaction with the Stockfish chess engine,
 * sending commands to it, and retrieving the output.
 */
class StockFishIntegration {
public:
    /**
     * @brief Constructor for StockFishIntegration.
     * @param enginePath The path to the Stockfish engine executable.
     */
    explicit StockFishIntegration(const QString &enginePath);

    /**
     * @brief Retrieves the output from the Stockfish process.
     * @param waitTime The time in milliseconds to wait for the output.
     * @return A QString containing the output from the Stockfish process.
     */
    auto getOutput(int waitTime) -> QString;

    /**
     * @brief Calculates the best move for the given FEN (Forsyth–Edwards Notation) string.
     * @param fen The FEN string representing the current board state.
     * @param waitTime The time in milliseconds to wait for the best move calculation.
     * @return A QString representing the best move as determined by Stockfish.
     */
    auto testBestMove(const QString &fen, int waitTime) -> QString;

    /**
     * @brief Destructor for StockFishIntegration.
     */
    ~StockFishIntegration();

private:
    /**
     * @brief Sends a command to the Stockfish process.
     * @param command The command to send to Stockfish.
     */
    auto sendCommand(const QString &command) -> void;

    QProcess stockfishProcess; ///< The process object for Stockfish.
    QString enginePath; ///< The path to the Stockfish engine executable.
};

#endif //QTCHESS_PJC_STOCKFISHINTEGRATION_H
