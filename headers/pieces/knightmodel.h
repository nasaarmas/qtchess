/**
 * @file knightmodel.h
 * @brief Definition of the KnightModel class, a derived class from PawnModel to represent a knight piece in a chess game.
 */

#ifndef QTCHESS_PJC_KNIGHTMODEL_H
#define QTCHESS_PJC_KNIGHTMODEL_H

#include "pawnmodel.h"
#include <QList>

/**
 * @class KnightModel
 * @brief Represents a knight piece in a chess game, extending the functionalities of the PawnModel class.
 *
 * KnightModel includes the capabilities to calculate possible moves, validate moves based on the game rules,
 * and handle state updates after moves specifically for a knight piece.
 */
class KnightModel : public PawnModel {
public:
    /**
     * @brief Constructs a KnightModel with specified position, image path, and color.
     * @param pwnBPosition The board position of the knight.
     * @param imagePath The path to the image representing the knight.
     * @param isWhite Flag indicating if the knight is white.
     */
    KnightModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    /**
     * @brief Calculates possible moves for the knight.
     * @param moveVector Vector to store possible moves.
     * @param pieces List of all pieces on the board.
     */
    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    /**
     * @brief Validates a move based on the game rules for the knight.
     * @param x The x-coordinate of the target position.
     * @param y The y-coordinate of the target position.
     * @return True if the move is valid, false otherwise.
     */
    auto ValidateMove(int x, int y) -> bool override;

    /**
     * @brief Performs any cleanup or state updates after a move for the knight.
     * @return Always returns false as there are no specific cleanup actions for the knight.
     */
    auto CleanUp() -> bool override;
};

#endif //QTCHESS_PJC_KNIGHTMODEL_H
