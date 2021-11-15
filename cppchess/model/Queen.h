#ifndef CHESS_MODEL_QUEEN
#define CHESS_MODEL_QUEEN

#include "Piece.h"

namespace Chess::Model
{
	class Queen : public Piece
	{
	public:
		Queen(Enums::Colour colour, Point position) : Piece(colour, position) {};
		Enums::PieceType GetType() const override { return Enums::QUEEN; }
	};
}

#endif // !CHESS_MODEL_Queen