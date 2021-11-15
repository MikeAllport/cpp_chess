#ifndef CHESS_MODEL_PAWN
#define CHESS_MODEL_PAWN

#include "Piece.h"

namespace Chess::Model
{
	class Pawn : public Piece
	{
	public:
		Pawn(Enums::Colour colour, Point position) : Piece(colour, position) {};
		Enums::PieceType GetType() const override { return Enums::PAWN; }
	};
}

#endif // !CHESS_MODEL_PAWN