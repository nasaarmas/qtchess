#ifndef QTCHESS_PJC_CHESSMODEL_H
#define QTCHESS_PJC_CHESSMODEL_H

#include <QList>
#include <QDebug>
#include "pawnmodel.h"
#include "bishopmodel.h"
#include "rookmodel.h"
#include "knightmodel.h"
#include "queenmodel.h"
#include "kingmodel.h"


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

    auto getMovesVector() -> QVector<BoardPosition>;

    auto ChangePiecePlace(quint8 x, quint8 y) -> void;

    auto startGame() -> void;

    auto stopGame() -> void;

    void popCurrentPieceFromMoves();

    auto isPieceSelected() -> bool;

    auto isKingAttacked() -> bool;

    auto getPieceClicked(quint8 column, quint8 row) -> void;

    auto isCellAttacked(quint8 column, quint8 row) -> bool;

    auto isMate() -> bool;


    ~ChessModel();

private:
    static auto initializePieces(QList<PawnModel *> &allPieces, PawnModel *&whiteKing, PawnModel *&blackKing) -> void;

    auto updateMoveVector(PawnModel *pChosenPawn) -> void;
    auto performCastling(quint8 x, quint8 y) -> void;
    auto PromotePawn() -> void;
    auto KillAtack(quint8 x, quint8 y) -> void;
    auto clearEnPassants() -> void;

    PawnModel *whiteKing;
    PawnModel *blackKing;
    bool isWhitePlayerTurn;
    QVector<BoardPosition> pPawnMovesVector;
    QList<PawnModel *> pieces;
    QList<PawnModel *> deadPieces;
    PawnModel *currentlySelectedPawn;
    int fontSize, lftBrdPadding, topBrdPadding, cellSize;
    bool isGameOn;


};

#endif //QTCHESS_PJC_CHESSMODEL_H
