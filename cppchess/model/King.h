#ifndef CHESS_MODEL_KING
#define CHESS_MODEL_KING

#include "Piece.h"

namespace Chess::Model
{
	class King : public Piece
	{
	public:
		King(Enums::Colour colour, Point position) : Piece(colour, position) {};
		Enums::PieceType GetType() const override { return Enums::KING; }
		bool HasMoved() { return hasMoved; };
		void SetMoved() { hasMoved = true; }
	private:
		bool hasMoved;
	};
}

#endif // !CHESS_MODEL_PAWN