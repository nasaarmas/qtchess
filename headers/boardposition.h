/**
 * @file boardposition.h
 * @brief Definition of the BoardPosition struct.
 *
 * This file contains the definition of the BoardPosition struct, which is used throughout the
 * chess game to represent the position of pieces on the chessboard.
 */

#ifndef QTCHESS_PJC_BOARDPOSITION_H
#define QTCHESS_PJC_BOARDPOSITION_H

#include <Qt>

/**
 * @struct BoardPosition
 * @brief Represents a position on the chessboard.
 *
 * This struct is used to represent a position on the chessboard with x (column) and y (row) coordinates.
 * The coordinates are zero-based, meaning (0,0) represents the top-left corner of the chessboard.
 */
struct BoardPosition {
    quint8 posX; ///< The x-coordinate (column) of the position.
    quint8 posY; ///< The y-coordinate (row) of the position.
};

#endif //QTCHESS_PJC_BOARDPOSITION_H
