#ifndef CHESS_MODEL_BOARD
#define CHESS_MODEL_BOARD

#include "Piece.h"
#include "../utils/FilterableList.h"

// forward declare friend class
namespace Chess::Controller
{
	class BoardController;
}

namespace Chess::Model
{
	class Board
	{
	public:
		Board() : board(std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr))) {};
		~Board() { for(Model::Piece* piece: activePieces.v) delete piece; }
		Piece* operator()(int x, int y) { return board[y][x]; }
		Piece* operator()(Point point) { return board[point.GetY()][point.GetX()]; }
		FilterableList<Piece*> ActivePieces() { return activePieces; }
		friend class Controller::BoardController;
	private:
		std::vector<std::vector<Piece*>> board;
		FilterableList<Piece*> activePieces;
	};
}
#endif // !CHESS_MODEL_BOARD
