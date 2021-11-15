#ifndef CHESS_MODEL_CASTLE
#define CHESS_MODEL_CASTLE

#include "Piece.h"

namespace Chess::Model
{
	class Castle : public Piece
	{
	public:
		Castle(Enums::Colour colour, Point position) : Piece(colour, position) {};
		Enums::PieceType GetType() const override { return Enums::CASTLE; }
	};
}

#endif // !CHESS_MODEL_Castle