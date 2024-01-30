#ifndef QTCHESS_PJC_CHESSMODEL_H
#define QTCHESS_PJC_CHESSMODEL_H

#include <QList>
#include "pawnmodel.h"
#include "bishopmodel.h"
#include "rookmodel.h"
#include "knightmodel.h"
#include "queenmodel.h"
#include "kingmodel.h"
#include <string>

/**
 * @class ChessModel
 * @brief Represents the game state and logic for a chess game.
 */
class ChessModel {
public:
    /**
     * @brief Default constructor for ChessModel.
     */
    ChessModel();

    /**
     * @brief Gets the left padding of the chess board.
     * @return The left padding.
     */
    [[nodiscard]] auto getLftPadding() const -> int;

    /**
     * @brief Gets the top padding of the chess board.
     * @return The top padding.
     */
    [[nodiscard]] auto getTopPadding() const -> int;

    /**
     * @brief Gets the cell size of the chess board.
     * @return The cell size.
     */
    [[nodiscard]] auto getCellSize() const -> int;

    /**
     * @brief Checks if the game is currently in progress.
     * @return True if the game is ongoing, false otherwise.
     */
    [[nodiscard]] auto GameOn() const -> bool;

    /**
     * @brief Gets the list of currently active pawn pieces.
     * @return The list of active pawns.
     */
    [[nodiscard]] auto getCurrentPieces() const -> QList<PawnModel *>;

    /**
     * @brief Gets the list of captured pawn pieces.
     * @return The list of dead pieces.
     */
    [[nodiscard]] auto getDeadPieces() const -> QList<PawnModel *>;

    /**
     * @brief Checks if it's the turn of the white player.
     * @return True if it's the turn of the white player, false otherwise.
     */
    [[nodiscard]] auto isWhiteTurn() const -> bool;

    /**
     * @brief Generates and returns the FEN (Forsyth–Edwards Notation) string for the current game state.
     * @return The FEN string.
     */
    [[nodiscard]] auto generateFEN() const -> QString;

    /**
     * @brief Gets the list of possible moves for the currently selected pawn.
     * @return The list of possible moves.
     */
    auto getMovesVector() -> QVector<BoardPosition>;

    /**
     * @brief Moves the currently selected pawn to the specified position.
     * @param x The column index.
     * @param y The row index.
     */
    auto ChangePiecePlace(quint8 x, quint8 y) -> void;

    /**
     * @brief Starts the chess game.
     */
    auto startGame() -> void;

    /**
     * @brief Stops the chess game.
     */
    auto stopGame() -> void;

    /**
     * @brief Removes the last move from the list of possible moves.
     */
    auto popCurrentPieceFromMoves() -> void;

    /**
     * @brief Checks if a pawn is currently selected.
     * @return True if a pawn is selected, false otherwise.
     */
    auto isPieceSelected() -> bool;

    /**
     * @brief Checks if the king is under attack.
     * @return True if the king is attacked, false otherwise.
     */
    auto isKingAttacked() -> bool;

    /**
     * @brief Gets the pawn clicked at the specified position.
     * @param column The column index.
     * @param row The row index.
     */
    auto getPieceClicked(quint8 column, quint8 row) -> void;

    /**
     * @brief Checks if a cell on the chessboard is under attack.
     * @param column The column index.
     * @param row The row index.
     * @return True if the cell is attacked, false otherwise.
     */
    auto isCellAttacked(quint8 column, quint8 row) -> bool;

    /**
     * @brief Checks if the game is in a checkmate state.
     * @return True if it's checkmate, false otherwise.
     */
    auto isMate() -> bool;

    /**
     * @brief Destructor for ChessModel.
     */
    ~ChessModel();

private:
    /**
     * @brief Initializes the pieces on the chessboard, including kings.
     * @param allPieces Reference to the list of all pieces on the chessboard.
     * @param whiteKing Reference to the white king pawn.
     * @param blackKing Reference to the black king pawn.
     */
    static auto initializePieces(QList<PawnModel *> &allPieces, PawnModel *&whiteKing, PawnModel *&blackKing) -> void;

    /**
     * @brief Updates the list of possible moves for the currently selected pawn.
     * @param pChosenPawn The currently selected pawn.
     */
    auto updateMoveVector(PawnModel *pChosenPawn) -> void;

    /**
     * @brief Performs castling move if valid.
     * @param x The column index of the destination cell.
     */
    auto performCastling(quint8 x) -> void;

    /**
     * @brief Promotes a pawn to a queen upon reaching the opposite end of the board.
     */
    auto PromotePawn() -> void;

    /**
     * @brief Handles the capture of an opponent's piece during a move.
     * @param x The column index of the destination cell.
     * @param y The row index of the destination cell.
     */
    auto KillAtack(quint8 x, quint8 y) -> void;

    /**
     * @brief Clears the en passant flags for all pawns.
     */
    auto clearEnPassants() -> void;

    /**
     * @brief Converts the pawn type to a character representation for FEN string.
     * @param piece The pawn model.
     * @return The character representation.
     */
    static auto pieceCharFromType(const PawnModel *piece) -> char;

    /**
     * @brief Finds and returns the pawn at the specified position.
     * @param x The column index.
     * @param y The row index.
     * @return Pointer to the pawn at the position, or nullptr if no pawn is found.
     */
    [[nodiscard]] auto findPieceAt(int x, int y) const -> PawnModel *;

    // Private member variables...
    PawnModel *whiteKing;             ///< Pointer to the white king pawn.
    PawnModel *blackKing;             ///< Pointer to the black king pawn.
    bool isWhitePlayerTurn;           ///< Flag indicating the turn of the white player.
    QVector<BoardPosition> pPawnMovesVector; ///< Vector storing possible moves for the currently selected pawn.
    QList<PawnModel *> pieces;        ///< List of all active pawn pieces.
    QList<PawnModel *> deadPieces;    ///< List of captured pawn pieces.
    PawnModel *currentlySelectedPawn; ///< Pointer to the currently selected pawn.
    int fontSize, lftBrdPadding, topBrdPadding, cellSize, turnNumber, fromLastKill; ///< Various game-related parameters.
    bool isGameOn;                    ///< Flag indicating whether the game is in progress.
};


#endif //QTCHESS_PJC_CHESSMODEL_H
