#ifndef CHESS_MOVE_CONTROLLER
#define CHESS_MOVE_CONTROLLER

#include "../model/AllPiecesInclude.h"
#include "../model/Board.h"
#include "../model/Move.h"
#include "../utils/FilterableList.h"
#include "../model/Player.h"

namespace Chess::Controller
{
	class MoveController
	{
	public:
		MoveController(Model::Board& board, Model::Player p1) : board(board), player(p1) {};
		FilterableList<Model::Move> GetMoves(Model::Piece* piece);
		FilterableList<Model::Move> GetMoves(Model::Pawn* piece);
		FilterableList<Model::Move> GetMoves(Model::Bishop* piece);
		FilterableList<Model::Move> GetMoves(Model::Horse* piece);
		FilterableList<Model::Move> GetMoves(Model::Castle* piece);
		FilterableList<Model::Move> GetMoves(Model::King* piece);
		FilterableList<Model::Move> GetMoves(Model::Queen* piece);
	private:
		FilterableList<Model::Move> GetDiagonalMoves(Model::Piece* piece);
		FilterableList<Model::Move> GetHorizontalMoves(Model::Piece* piece);
		FilterableList<Model::Move> GetVerticalMoves(Model::Piece* piece);
		bool AddPieceMove(FilterableList<Model::Move>& addToList, Model::Piece* piece, int x, int y);
		Model::Board& board;
		Model::Player player;
	};
}
#endif // !CHESS_MOVE_CONTROLLER
