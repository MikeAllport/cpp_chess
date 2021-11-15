#ifndef CHESS_CONTROLLER_BOARD
#define CHESS_CONTROLLER_BOARD

#include "../model/Board.h"
#include "../model/Move.h"
#include "../model/AllPiecesInclude.h"
#include "../model/Player.h"

namespace Chess::Controller
{
    class BoardController
    {
    public:
        BoardController(Model::Board& board, Model::Player& player): 
            board(board),
            player(player) {};
        void AddPiece(Model::Piece* piece);
        void MakeMove(Model::Move move);
        Model::Piece* TakePiece(Model::Point);
        void PlacePiece(Model::Piece* piece, Model::Point place);
        void RemovePiece(Model::Piece* piece);
    private:
        void PawnToQueenCheck(Model::Pawn* piece);
        void CastleWhiteKing(Model::King* king, Model::Move move);
        void CastleBlackKing(Model::King* king, Model::Move move);
        Model::Board& board;
        Model::Player& player;
    };
}

#endif