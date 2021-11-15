#ifndef CHESS_MODEL_BOARD
#define CHESS_MODEL_BOARD

#include "Piece.h"
#include "../utils/VectorHelper.h"

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
		Board(const Board& other): board(std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr))) {
			for(int i = 0; i < (int)board.size(); ++i)
			{
				for(int j = 0; j < (int)board[i].size(); ++j)
				{
					if(other.board[i][j])
					{
						board[i][j] = other.board[i][j]->Copy();
						activePieces.v.push_back(board[i][j]);
					}
				}
			}
		}
		~Board() { for(Model::Piece* piece: activePieces.v) delete piece; }
		Piece* operator()(int x, int y) { return board[y][x]; }
		Piece* operator()(Point point) { return board[point.GetY()][point.GetX()]; }
		VectorHelper<Piece*> ActivePieces() { return activePieces; }
		friend class Controller::BoardController;
	private:
		std::vector<std::vector<Piece*>> board;
		VectorHelper<Piece*> activePieces;
	};
}
#endif // !CHESS_MODEL_BOARD
