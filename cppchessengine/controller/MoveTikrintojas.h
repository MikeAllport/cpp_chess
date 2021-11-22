#ifndef CHESS_CONTROLLER_MOVETIKRINTOJAS
#define CHESS_CONTROLLER_MOVETIKRINTOJAS

/*
    First file to be commented, given naming. Partner and I could not decide between
    move evaluator or move validator, so gave it a lithuanian name for checker.

    This pure abstract class defines a method to validate a move. The concrete class's
    will have to implement this to return true/false if a move is valid
*/
#include "BoardController.h"
#include "../model/Board.h"
#include "../model/Piece.h"
#include "../model/Move.h"

namespace ChessEngine::Controller
{
    class MoveController;

    class MoveTikrintojas
    {
    public:
        MoveTikrintojas(Model::Board& board, BoardController& c_board): 
            board(board), c_board(c_board) {}
        virtual bool IsMoveValid(Model::Move move, MoveController& c_move) const = 0;
    protected:
        Model::Board& board;
        BoardController& c_board;
    };
}
#endif