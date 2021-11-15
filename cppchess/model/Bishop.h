#ifndef CHESS_MODEL_BISHOP
#define CHESS_MODEL_BISHOP

#include "Piece.h"

namespace Chess::Model
{
	class Bishop : public Piece
	{
	public:
		Bishop(Enums::Colour colour, Point position) : Piece(colour, position) {};

		Piece* Copy() override { return (Piece*) new Bishop(*this); }
		Enums::PieceType GetType() const override { return Enums::BISHOP; }
	};
}

#endif // !CHESS_MODEL_Bishop