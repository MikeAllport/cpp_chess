#include "DadsMoveTikrintojas.h"

namespace Chess::Controller
{
    bool DadsMoveTikrintojas::IsMoveValid(const Model::Move move, MoveController& c_move) const
    {
        if(IsColourAttacking(move, c_move))
        {
            return move.IsAttack();
        }
        return true;
    }

    bool DadsMoveTikrintojas::IsColourAttacking(const Model::Move move, MoveController& c_move) const
    {
        Model::Piece* pieceBeingMoved = c_board.GetPieceSafe(move.FromPosition());
        return c_board.ActivePieces().Filter([pieceBeingMoved, &c_move](Model::Piece* piece) {
                bool pieceAttackingAndSameColour = false;
                if(piece->IsWhite() == pieceBeingMoved->IsWhite())
                {
                    bool pieceAttackingAndSameColour = c_move.GetMoves(piece).Filter([](Model::Move move) { return move.IsAttack(); }).v.size() > 0 ;
                }
                return pieceAttackingAndSameColour;
            }).v.size() > 0;
    }
}