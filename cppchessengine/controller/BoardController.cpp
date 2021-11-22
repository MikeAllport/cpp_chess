#include "BoardController.h"

namespace ChessEngine::Controller
{
    void BoardController::AddPiece(Model::Piece* piece)
    {
        PlacePiece(piece, piece->GetPosition());
        board->activePieces.v.push_back(piece);
    }

    void BoardController::AddPiece(std::vector<Model::Piece*> pieces)
    {
        for(Model::Piece* piece: pieces)
        {
            AddPiece(piece);
        }
    }
    
    void BoardController::InitialiseBoard()
    {
        *board = ChessEngine::Model::Board();
        auto bottomColour = player->IsWhite()? Model::Enums::WHITE: Model::Enums::BLACK;
        auto topColour = player->IsWhite()? Model::Enums::BLACK: Model::Enums::WHITE;
        // place pawns
        for(int i = 0; i < 8; ++i)
        {
            auto topPawn = new Model::Pawn(topColour, Model::Point(i, 1));
            auto bottomPawn = new Model::Pawn(bottomColour, Model::Point(i, 6));
            AddPiece({topPawn, bottomPawn});
        }

        // place doubles
        for(int i = 0; i < 2; ++i)
        {
            int topY = 0, bottomY = 7;

            int xPos = i*7;
            auto castleTop = new Model::Castle(topColour, Model::Point(xPos, topY));
            auto castleBottom = new Model::Castle(bottomColour, Model::Point(xPos, bottomY));

            xPos = i * 5 + 1;
            auto horseTop = new Model::Horse(topColour, Model::Point(xPos, topY));
            auto horseBottom = new Model::Horse(bottomColour, Model::Point(xPos, bottomY));

            xPos = i * 3 + 2;
            auto bishopTop = new Model::Bishop(topColour, Model::Point(xPos, topY));
            auto bishopBottom = new Model::Bishop(bottomColour, Model::Point(xPos, bottomY));

            AddPiece({castleBottom, castleTop, horseBottom, horseTop, bishopBottom, bishopTop});
        }

        // king queen
        auto queenTop = new Model::Queen(topColour, Model::Point(3, 0));
        auto queenBottom = new Model::Queen(bottomColour, Model::Point(3, 7));
        auto kingTop = new Model::King(topColour, Model::Point(4, 0));
        auto kingBottom = new Model::King(bottomColour, Model::Point(4, 7));

        AddPiece({queenTop, queenBottom, kingTop, kingBottom});
    }

    VectorHelper<Model::Piece*> BoardController::ActivePieces()
    {
        return board->ActivePieces();
    }

    Model::Piece* BoardController::GetPieceSafe(const int x, const int y)
    {
        return x < 0 || x > 7 || y < 0 || y > 7? nullptr: (*board)(x, y);
    }

    Model::Piece* BoardController::GetPieceSafe(Model::Point position)
    {
        return GetPieceSafe(position.GetX(), position.GetY());
    }

    Model::King* BoardController::GetKing(bool isWhiteKing)
    {
        return (Model::King*)board->ActivePieces().Filter([isWhiteKing](Model::Piece* piece){ return piece->IsWhite() == isWhiteKing && piece->GetType() == Model::Enums::KING; }).v[0];
    }

    Model::King* BoardController::GetKing(Model::Enums::Colour colour)
    {
        return GetKing(colour == Model::Enums::WHITE? true: false);
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
        Model::Piece* returnPiece = (*board)(from);
        board->board[from.GetY()][from.GetX()] = nullptr;
        return returnPiece;
    }

    void BoardController::PlacePiece(Model::Piece* piece, Model::Point place)
    {
        piece->MoveTo(place);
        Model::Piece* takenPiece = (*board)(place);
        board->board[place.GetY()][place.GetX()] = piece;
        if (takenPiece)
        {
            RemovePiece(takenPiece);
        }
    }

    void BoardController::RemovePiece(Model::Piece* piece)
    {
        board->activePieces = board->activePieces.Filter([&piece](Model::Piece* toInspect) { return piece != toInspect;});
        delete piece;
    }

    void BoardController::PawnToQueenCheck(Model::Pawn* piece)
    {
        if(player->IsWhite())
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
        if(player->IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(0, 7), ChessEngine::Model::Point(3,7), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(7,7), ChessEngine::Model::Point(5,7), false));
            }
        }
        else if (!player->IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(0,0), ChessEngine::Model::Point(0,3), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(7,0), ChessEngine::Model::Point(0,5), false));
            }
        }
    }

    void BoardController::CastleBlackKing(Model::King* king, Model::Move move)
    {
        if(player->IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(0,0), ChessEngine::Model::Point(3,0), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(7,0), ChessEngine::Model::Point(5,0), false));
            }
        }
        else if (!player->IsWhite() && move.FromPosition().GetX() == 4)
        {
            if(move.ToPosition().GetX() == 2)
            {
                // move left castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(0,7), ChessEngine::Model::Point(3,7), false));
            }
            if(move.ToPosition().GetX() == 6)
            {
                // move right castle
                MakeMove(ChessEngine::Model::Move(ChessEngine::Model::Point(7,7), ChessEngine::Model::Point(5,7), false));
            }
        }
    }
}