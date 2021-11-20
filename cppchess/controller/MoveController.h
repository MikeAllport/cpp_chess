#ifndef CHESS_MOVE_CONTROLLER
#define CHESS_MOVE_CONTROLLER

#include "../model/AllPiecesInclude.h"
#include "MoveTikrintojas.h"
#include "../model/Board.h"
#include "../model/Move.h"
#include "../utils/VectorHelper.h"
#include "../model/Player.h"
#include <map>
#include "../utils/MapHelper.h"

namespace Chess::Controller
{
	class MoveController
	{
	public:
		MoveController(Model::Board& board, MoveTikrintojas& c_moveCheck, const Model::Player& p1) : 
		board(&board), 
		player(&p1),
		c_moveCheck(&c_moveCheck) {};
		MoveController(){};
		// returns all valid moves for colour, arrange in a dictionary of Point/Move values, point being origin
		std::map<Chess::Model::Point, VectorHelper<Chess::Model::Move>> GetAllColoursMoves(const Chess::Model::Enums::Colour colour);

		// returns all valid moves for a piece using MoveTikrintojas
		VectorHelper<Chess::Model::Move> GetValidMoves(Model::Piece* piece) {
            return GetMoves(piece).Filter([this](Model::Move x){ return c_moveCheck->IsMoveValid(x, *this); });
        };

		// gets all moves a piece can make, valie or invalid
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
		void AddCastlingMove(VectorHelper<Model::Move>& addToList, Model::King* piece);
		bool AddPieceMove(VectorHelper<Model::Move>& addToList, Model::Piece* piece, int x, int y);
		Model::Board* board;
		MoveTikrintojas* c_moveCheck;
		const Model::Player* player;
	};
}
#endif // !CHESS_MOVE_CONTROLLER
