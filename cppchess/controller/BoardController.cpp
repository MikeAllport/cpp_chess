#include "BoardController.h"

namespace Chess::Controller
{
    void BoardController::AddPiece(Model::Piece* piece)
    {
        PlacePiece(piece, piece->GetPosition());
        board.activePieces.v.push_back(piece);
    }

    void BoardController::MakeMove(Model::Move move) 
    { 
        Model::Piece* pieceFrom = TakePiece(move.FromPosition());
        PlacePiece(pieceFrom, move.ToPosition());
        switch(pieceFrom->GetType())
        {
            case Model::Enums::PAWN :
                PawnToQueenCheck((Model::Pawn*)pieceFrom);
                break;
            case Model::Enums::KING :
                if (pieceFrom->IsWhite())
                {
                    CastleWhiteKing((Model::King*)pieceFrom, move);
                }
                else
                {
                    CastleBlackKing((Model::King*)pieceFrom, move);
                }
                break;
        }
    }

    Model::Piece* BoardController::TakePiece(Model::Point from) 
    {
        Model::Piece* returnPiece = board(from);
        board.board[from.GetY()][from.GetX()] = nullptr;
        return returnPiece;
    }

    void BoardController::PlacePiece(Model::Piece* piece, Model::Point place)
    {
        piece->MoveTo(place);
        Model::Piece* takenPiece = board(place);
        board.board[place.GetY()][place.GetX()] = piece;
        if (takenPiece)
        {
            RemovePiece(takenPiece);
        }
    }

    void BoardController::RemovePiece(Model::Piece* piece)
    {
        board.activePieces = board.activePieces.Filter([&piece](Model::Piece* toInspect) { return piece != toInspect;});
        delete piece;
    }

    void BoardController::PawnToQueenCheck(Model::Pawn* piece)
    {
        if(player.IsWhite())
        {
            if(piece->IsWhite() && piece->GetPosition().GetY() == 0)
            {
                AddPiece(new Model::Queen(Model::Enums::WHITE, piece->GetPosition()));
            }
            else if (!piece->IsWhite() && piece->GetPosition().GetY() == 7)
            {
                AddPiece(new Model::Queen(Model::Enums::BLACK, piece->GetPosition()));
            }
        }
        else
        {
            if(piece->IsWhite() && piece->GetPosition().GetY() == 7)
            {
                AddPiece(new Model::Queen(Model::Enums::WHITE, piece->GetPosition()));
            }
            else if (!piece->IsWhite() && piece->GetPosition().GetY() == 0)
            {
                AddPiece(new Model::Queen(Model::Enums::BLACK, piece->GetPosition()));
            }            
        }
    }

    void BoardController::CastleWhiteKing(Model::King* king, Model::Move move)
    {
        if(player.IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(7,0), Chess::Model::Point(7,3), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(7,7), Chess::Model::Point(7,5), false));
            }
        }
        else if (!player.IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(0,0), Chess::Model::Point(0,3), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(0,0), Chess::Model::Point(0,3), false));
            }
        }
    }

    void BoardController::CastleBlackKing(Model::King* king, Model::Move move)
    {
        if(player.IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(0,0), Chess::Model::Point(0,3), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(0,0), Chess::Model::Point(0,3), false));
            }
        }
        else if (!player.IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(7,0), Chess::Model::Point(7,3), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(Chess::Model::Move(Chess::Model::Point(7,7), Chess::Model::Point(7,5), false));
            }
        }
    }

    Model::Piece* BoardController::GetPieceSafe(const int x, const int y)
    {
        return x < 0 || x > 7 || y < 0 || y > 7? nullptr: board(x, y);
    }

    Model::King* BoardController::GetKing(bool isWhiteKing)
    {
        return (Model::King*)board.ActivePieces().Filter([isWhiteKing](Model::Piece* piece){ return piece->IsWhite() == isWhiteKing && piece->GetType() == Model::Enums::KING; }).v[0];
    }
}