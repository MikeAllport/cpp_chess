#ifndef CHESS_CONTROLLER_BOARD
#define CHESS_CONTROLLER_BOARD

#include "../model/Board.h"
#include "../model/Move.h"
#include "../model/AllPiecesInclude.h"
#include "../model/Player.h"

namespace ChessEngine::Controller
{
    class BoardController
    {
    public:
        BoardController(Model::Board& board, const Model::Player& player): 
            board(&board),
            player(&player) { };
        BoardController(){};
        void InitialiseBoard();
        void AddPiece(Model::Piece* piece);
        void AddPiece(std::vector<Model::Piece*> pieces);
        void MakeMove(Model::Move move);
        Model::Piece* TakePiece(Model::Point);
        void PlacePiece(Model::Piece* piece, Model::Point place);
        void RemovePiece(Model::Piece* piece);
        VectorHelper<Model::Piece*> ActivePieces();
        Model::Piece* GetPieceSafe(Model::Point position);
        Model::Piece* GetPieceSafe(int x, int y);
        Model::King* GetKing(bool isWhiteKing);
        Model::King* GetKing(Model::Enums::Colour colour);
    private:
        void PawnToQueenCheck(Model::Pawn* piece);
        void CastleWhiteKing(Model::King* king, Model::Move move);
        void CastleBlackKing(Model::King* king, Model::Move move);
        Model::Board* board;
        const Model::Player* player;
    };
}

#endif