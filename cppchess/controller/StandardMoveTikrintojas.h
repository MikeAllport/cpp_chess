#ifndef CHESS_CONTROLLER_STANDARDMOVETIKRINTOJAS
#define CHESS_CONTROLLER_STANDARDMOVETIKRINTOJAS

#include "MoveTikrintojas.h"

namespace Chess::Controller
{
    class StandardMoveTikrintojas: public MoveTikrintojas
    {
    public:
        StandardMoveTikrintojas(Model::Board& board, BoardController& c_board):
            MoveTikrintojas(board, c_board) {};
        bool IsMoveValid(Model::Move move, MoveController& c_move) const override;
    protected:
        bool IsKingUnderAttack(const bool isWhiteKing, MoveController& c_move) const;
    };
}

#endif