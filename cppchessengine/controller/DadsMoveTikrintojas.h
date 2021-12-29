#ifndef CHESS_CONTROLLER_DADSMOVETIKRINTOJAS
#define CHESS_CONTROLLER_DADSMOVETIKRINTOJAS

#include "MoveTikrintojas.h"
#include "MoveController.h"

namespace ChessEngine::Controller
{
    class DadsMoveTikrintojas: public MoveTikrintojas
    {
    public:
        DadsMoveTikrintojas(Model::Board& board, BoardController& c_board):
            MoveTikrintojas(board, c_board) {};
        bool IsMoveValid(const Model::Move move, MoveController& c_move) const override;
    protected:
        bool IsColourAttacking(const Model::Move move, MoveController& c_move) const;
    };
}

#endif