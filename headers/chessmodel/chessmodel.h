#ifndef QTCHESS_PJC_CHESSMODEL_H
#define QTCHESS_PJC_CHESSMODEL_H

#include <QList>
#include "../pieces/pawnmodel.h"
#include "../pieces/bishopmodel.h"
#include "../pieces/rookmodel.h"
#include "../pieces/knightmodel.h"
#include "../pieces/queenmodel.h"
#include "../pieces/kingmodel.h"
#include <string>


class ChessModel {
public:
    ChessModel();

    [[nodiscard]] auto getLftPadding() const -> int;

    [[nodiscard]] auto getTopPadding() const -> int;

    [[nodiscard]] auto getCellSize() const -> int;

    [[nodiscard]] auto GameOn() const -> bool;

    [[nodiscard]] auto getCurrentPieces() const -> QList<PawnModel *>;

    [[nodiscard]] auto getDeadPieces() const -> QList<PawnModel *>;

    [[nodiscard]] auto isWhiteTurn() const -> bool;

    [[nodiscard]] auto generateFEN() const -> QString;

    auto getMovesVector() -> QVector<BoardPosition>;

    auto ChangePiecePlace(quint8 x, quint8 y) -> void;

    auto startGame() -> void;

    auto stopGame() -> void;

    auto popCurrentPieceFromMoves() -> void;

    auto isPieceSelected() -> bool;

    auto isKingAttacked() -> bool;

    auto getPieceClicked(quint8 column, quint8 row) -> void;

    auto isCellAttacked(quint8 column, quint8 row) -> bool;

    auto isMate() -> bool;

    ~ChessModel();

private:
    static auto initializePieces(QList<PawnModel *> &allPieces, PawnModel *&whiteKing, PawnModel *&blackKing) -> void;

    auto updateMoveVector(PawnModel *pChosenPawn) -> void;

    auto performCastling(quint8 x) -> void;

    auto PromotePawn() -> void;

    auto KillAtack(quint8 x, quint8 y) -> void;

    auto clearEnPassants() -> void;

    auto restorePiece(PawnModel *capturedPiece, int capturedPieceIndex) -> void;

    auto removePieceAt(const BoardPosition &position, PawnModel *&capturedPiece, int &capturedPieceIndex) -> void;

    auto simulatesCheck(PawnModel *pChosenPawn, const BoardPosition &move) -> bool;

    static auto pieceCharFromType(const PawnModel *piece) -> char;

    [[nodiscard]] auto findPieceAt(int x, int y) const -> PawnModel *;

    PawnModel *whiteKing;
    PawnModel *blackKing;
    bool isWhitePlayerTurn;
    QVector<BoardPosition> pPawnMovesVector;
    QList<PawnModel *> pieces;
    QList<PawnModel *> deadPieces;
    PawnModel *currentlySelectedPawn;
    int fontSize, lftBrdPadding, topBrdPadding, cellSize, turnNumber, fromLastKill;
    bool isGameOn;
};

#endif //QTCHESS_PJC_CHESSMODEL_H
