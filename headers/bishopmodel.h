/**
 * @file bishopmodel.h
 * @brief Definition of the BishopModel class.
 *
 * The BishopModel class represents a bishop in a game of chess and inherits from PawnModel.
 * It encapsulates the properties and behavior specific to a bishop, such as its possible moves
 * and movement validation.
 */

#ifndef QTCHESS_PJC_BISHOPMODEL_H
#define QTCHESS_PJC_BISHOPMODEL_H

#include "pawnmodel.h"

/**
 * @class BishopModel
 * @brief Represents a bishop in a chess game.
 *
 * This class provides functionalities specific to a bishop, including the ability to calculate
 * possible moves, validate a move, and handle cleanup operations post-move if necessary.
 */
class BishopModel : public PawnModel {
public:
    BishopModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    /**
     * Calculates possible moves for the bishop.
     * @param moveVector Reference to the vector where possible moves will be stored.
     * @param pieces Constant reference to the list of pieces on the board.
     */
    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    /**
     * Cleanup operations after the bishop moves (if any).
     * @return A boolean indicating if cleanup was performed.
     */
    auto CleanUp() -> bool override;

    /**
     * Validates if a move is legal for the bishop.
     * @param x X-coordinate of the target position.
     * @param y Y-coordinate of the target position.
     * @return A boolean indicating if the move is valid.
     */
    auto ValidateMove(int x, int y) -> bool override;
};

#endif //QTCHESS_PJC_BISHOPMODEL_H
