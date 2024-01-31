/**
 * @file rookmodel.h
 * @brief Definition of the RookModel class, a derived class from PawnModel to represent a rook piece in a chess game.
 */

#ifndef QTCHESS_PJC_ROOKMODEL_H
#define QTCHESS_PJC_ROOKMODEL_H

#include <QList>
#include "pawnmodel.h"

/**
 * @class RookModel
 * @brief Represents a rook piece in a chess game, extending the functionalities of the PawnModel class.
 *
 * RookModel includes the capabilities to calculate possible moves, validate moves based on the game rules,
 * and handle state updates after moves specifically for a rook piece.
 */
class RookModel : public PawnModel {
public:
    /**
     * @brief Constructs a RookModel with specified position, image path, and color.
     * @param pwnBPosition The board position of the rook.
     * @param imagePath The path to the image representing the rook.
     * @param isWhite Flag indicating if the rook is white.
     */
    RookModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    /**
     * @brief Calculates possible moves for the rook.
     * @param moveVector Vector to store possible moves.
     * @param pieces List of all pieces on the board.
     */
    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    /**
     * @brief Validates a move based on the game rules for the rook.
     * @param x The x-coordinate of the target position.
     * @param y The y-coordinate of the target position.
     * @return True if the move is valid, false otherwise.
     */
    auto ValidateMove(int x, int y) -> bool override;

    /**
     * @brief Performs any cleanup or state updates after a move for the rook.
     * @return True if any cleanup was performed, false otherwise.
     */
    auto CleanUp() -> bool override;
};

#endif //QTCHESS_PJC_ROOKMODEL_H
