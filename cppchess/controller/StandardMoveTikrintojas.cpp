#include "StandardMoveTikrintojas.h"
#include "MoveController.h"

namespace Chess::Controller
{
    bool StandardMoveTikrintojas::IsMoveValid(Model::Move move, MoveController& c_move) const
    {
        // get copy of piece in the from position
        Model::Piece* pieceFromPosition = board(move.FromPosition().GetX(), move.FromPosition().GetY())->Copy();
        
        // get copy of piece in the to position
        Model::Piece* pieceInToPos = board(move.ToPosition().GetX(), move.ToPosition().GetY());
        if (pieceInToPos)
        {
            pieceInToPos = pieceInToPos->Copy();
        }

        // make the move
        c_board.MakeMove(move);

        bool moveValid = !IsKingUnderAttack(pieceFromPosition->IsWhite(), c_move);

        // revert move
        if(pieceInToPos)
        {
            c_board.AddPiece(pieceInToPos);
        }
        else
        {
            c_board.RemovePiece(c_board.TakePiece(move.ToPosition()));
        }
        c_board.AddPiece(pieceFromPosition);
        return moveValid;
    };

    bool StandardMoveTikrintojas::IsKingUnderAttack(const bool isWhiteKing, MoveController& c_move) const
    {
        Model::King* king = c_board.GetKing(isWhiteKing);
        
        // loops through all opposing pieces
        for(Model::Piece* piece: board.ActivePieces().Filter([king](Model::Piece* piece){ return piece->IsWhite() != king->IsWhite(); }).v)
        {
            // loops through all pieces moves to find if it contains kings position
            if(c_move.GetMoves(piece).Filter([king](Model::Move move) { return move.ToPosition() == king->GetPosition(); }).v.size() > 0)
            {
                return true;
            }
        }
        return false;
    };
}