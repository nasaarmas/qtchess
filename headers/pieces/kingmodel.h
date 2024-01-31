/**
 * @file kingmodel.h
 * @brief Definition of the KingModel class, a derived class from PawnModel to represent a king piece in a chess game.
 */

#ifndef QTCHESS_PJC_KINGMODEL_H
#define QTCHESS_PJC_KINGMODEL_H

#include <QList>
#include "pawnmodel.h"

/**
 * @class KingModel
 * @brief Represents a king piece in a chess game, extending the functionalities of the PawnModel class.
 *
 * KingModel includes the capabilities to calculate possible moves, validate moves based on the game rules,
 * and handle state updates after moves specifically for a king piece.
 */
class KingModel : public PawnModel {
public:
    /**
     * @brief Constructs a KingModel with specified position, image path, and color.
     * @param pwnBPosition The board position of the king.
     * @param imagePath The path to the image representing the king.
     * @param isWhite Flag indicating if the king is white.
     */
    KingModel(BoardPosition pwnBPosition, QString imagePath, bool isWhite = true);

    /**
     * @brief Calculates possible moves for the king, including castling if applicable.
     * @param moveVector Vector to store possible moves.
     * @param pieces List of all pieces on the board.
     */
    auto PossibleMoves(QVector<BoardPosition> *moveVector, const QList<PawnModel *> &pieces) -> void override;

    /**
     * @brief Validates a move based on the game rules for the king.
     * @param x The x-coordinate of the target position.
     * @param y The y-coordinate of the target position.
     * @return True if the move is valid, false otherwise.
     */
    auto ValidateMove(int x, int y) -> bool override;

    /**
     * @brief Performs any cleanup or state updates after a move for the king.
     * @return True if any cleanup was performed, false otherwise.
     */
    auto CleanUp() -> bool override;
};

#endif //QTCHESS_PJC_KINGMODEL_H
