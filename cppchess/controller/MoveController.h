#ifndef CHESS_MOVE_CONTROLLER
#define CHESS_MOVE_CONTROLLER

#include "../model/AllPiecesInclude.h"
#include "../model/Board.h"
#include "../model/Move.h"
#include "../utils/VectorHelper.h"
#include "../model/Player.h"

namespace Chess::Controller
{
	class MoveController
	{
	public:
		MoveController(Model::Board& board, Model::Player p1) : board(board), player(p1) {};
		VectorHelper<Model::Move> GetMoves(Model::Piece* piece);
		VectorHelper<Model::Move> GetMoves(Model::Pawn* piece);
		VectorHelper<Model::Move> GetMoves(Model::Bishop* piece);
		VectorHelper<Model::Move> GetMoves(Model::Horse* piece);
		VectorHelper<Model::Move> GetMoves(Model::Castle* piece);
		VectorHelper<Model::Move> GetMoves(Model::King* piece);
		VectorHelper<Model::Move> GetMoves(Model::Queen* piece);
	private:
		VectorHelper<Model::Move> GetDiagonalMoves(Model::Piece* piece);
		VectorHelper<Model::Move> GetHorizontalMoves(Model::Piece* piece);
		VectorHelper<Model::Move> GetVerticalMoves(Model::Piece* piece);
		bool AddPieceMove(VectorHelper<Model::Move>& addToList, Model::Piece* piece, int x, int y);
		Model::Board& board;
		Model::Player player;
	};
}
#endif // !CHESS_MOVE_CONTROLLER
