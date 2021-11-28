#include "StandardMoveTikrintojas.h"
#include "MoveController.h"

namespace ChessEngine::Controller
{
    bool StandardMoveTikrintojas::IsMoveValid(const Model::Move move, MoveController& c_move) const
    {
        // get copy of piece in the from position
        Model::Piece* pieceFromPosition = board(move.FromPosition().GetX(), move.FromPosition().GetY());
        bool pieceMoved = false;
        // gets moved status
        auto castle = dynamic_cast<Model::Castle*>(pieceFromPosition);
        auto king = dynamic_cast<Model::King*>(pieceFromPosition);
        auto pawn = dynamic_cast<Model::Pawn*>(pieceFromPosition);
        if(castle)
        {
            pieceMoved = castle->HasMoved();
        }
        else if(king)
        {
            pieceMoved = king->HasMoved();
        }
        else if(pawn)
        {
            pieceMoved = pawn->HasMoved();
        }
        
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
        c_board.MakeMove(Model::Move(move.ToPosition(), move.FromPosition(), false));
        if(pieceInToPos)
        {
            c_board.AddPiece(pieceInToPos);
        }

        // revert castle
        if(move.FromPosition().GetX() == 4)
        {
            int fromYPos =  move.FromPosition().GetY();
            if(move.ToPosition().GetX() == 6)
            {
                auto castle = dynamic_cast<Model::Castle*>(c_board.GetPieceSafe(Model::Point(5, fromYPos)));
                c_board.MakeMove(Model::Move(castle->GetPosition(), Model::Point(7, fromYPos), false));
                castle->SetMoved(false);
            }
            else if(move.ToPosition().GetX() == 2)
            {
                auto castle = dynamic_cast<Model::Castle*>(c_board.GetPieceSafe(Model::Point(3, fromYPos)));
                c_board.MakeMove(Model::Move(castle->GetPosition(), Model::Point(0, fromYPos), false));
                castle->SetMoved(false);
            }
        }

        // revert moved status
        if(castle)
        {
            castle->SetMoved(pieceMoved);
        }
        else if(king)
        {
            king->SetMoved(pieceMoved);
        }
        else if(pawn)
        {
            pawn->SetMoved(pieceMoved);
        }
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