/**
 * @file pawnmodel.h
 * @brief Definition of the PawnModel class, a base class for pawn pieces in a chess game.
 */

#ifndef QTCHESS_PJC_PAWNMODEL_H
#define QTCHESS_PJC_PAWNMODEL_H

#include "../boardposition.h"
#include <QVector>
#include <memory>

/**
 * @class PawnModel
 * @brief Represents a pawn piece in a chess game, holding its state and behavior.
 *
 * The PawnModel class provides the basic functionalities of a pawn piece in a chess game,
 * including its position, image, color, and possible moves. It serves as a base class
 * for more specific pawn types.
 */
class PawnModel {

public:
    /**
     * @brief Constructs a PawnModel with specified position, image path, and color.
     * @param pwnBPosition The board position of the pawn.
     * @param imagePath The path to the image representing the pawn.
     * @param isWhite Flag indicating if the pawn is white.
     */
    PawnModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    /**
     * @brief Calculates possible moves for the pawn.
     * @param moveVector Vector to store possible moves.
     * @param pieces List of all pieces on the board.
     */
    virtual auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void;

    /**
     * @brief Validates a move based on the game rules.
     * @param x The x-coordinate of the target position.
     * @param y The y-coordinate of the target position.
     * @return True if the move is valid, false otherwise.
     */
    virtual auto ValidateMove(int x, int y) -> bool;

    /**
     * @brief Performs any cleanup or state updates after a move.
     * @return True if any cleanup was performed, false otherwise.
     */
    virtual auto CleanUp() -> bool;

    virtual ~PawnModel() = default;

    bool isUpgradable; ///< Indicates if the pawn is in a position to be upgraded.
    BoardPosition pwnBPosition; ///< Current board position of the pawn.
    QString imagePath; ///< Path to the image representing the pawn.
    bool isWhite; ///< Flag indicating if the pawn is white.
    BoardPosition allowSpecialMove{}; ///< Special move allowed for the pawn (e.g., 'en passant').
    bool isFirstMove; ///< Flag to indicate if it's the pawn's first move.
};

#endif //QTCHESS_PJC_PAWNMODEL_H
