#ifndef CHESS_MODEL_HORSE
#define CHESS_MODEL_HORSE

#include "Piece.h"

namespace Chess::Model
{
	class Horse : public Piece
	{
	public:
		Horse(Enums::Colour colour, Point position) : Piece(colour, position) {};
		Enums::PieceType GetType() const override { return Enums::HORSE; }
	};
}

#endif // !CHESS_MODEL_Horse