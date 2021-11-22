#ifndef CHESS_MODEL_BOARD
#define CHESS_MODEL_BOARD

#include "Piece.h"
#include "../utils/VectorHelper.h"

// forward declare friend class
namespace ChessEngine::Controller
{
	class BoardController;
}

namespace ChessEngine::Model
{
	class Board
	{
	public:
		Board() : board(std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr))) {};
		Board(const Board& other): board(std::vector<std::vector<Piece*>>(8, std::vector<Piece*>(8, nullptr))) {
			Copy(other);
		}
		~Board() 
		{ 
			for(Model::Piece* piece: activePieces.v) 
				delete piece; 
		}
		Board& operator=(const Board& other){
			Copy(other);
			return *this;
		}
		Piece* operator()(int x, int y) { return board[y][x]; }
		Piece* operator()(Point point) { return board[point.GetY()][point.GetX()]; }
		VectorHelper<Piece*> ActivePieces() { return activePieces; }
		friend class Controller::BoardController;
	private:
		void Copy(const Board& other) {
			for(int i = 0; i < (int)board.size(); ++i)
			{
				for(int j = 0; j < (int)board[i].size(); ++j)
				{						
					if(board[i][j])
					{
						Piece* pieceAtPosition = board[i][j];
						activePieces = activePieces.Filter([pieceAtPosition](Piece* pieceInPieces){ return pieceInPieces != pieceAtPosition; });
						delete board[i][j];
						board[i][j] = nullptr;
					}
					if(other.board[i][j])
					{
						board[i][j] = other.board[i][j]->Copy();
						activePieces.v.push_back(board[i][j]);
					}
				}
			}
		}
		std::vector<std::vector<Piece*>> board;
		VectorHelper<Piece*> activePieces;
	};
}
#endif // !CHESS_MODEL_BOARD
