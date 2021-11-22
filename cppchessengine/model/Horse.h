#ifndef CHESS_MODEL_HORSE
#define CHESS_MODEL_HORSE

#include "Piece.h"

namespace ChessEngine::Model
{
	class Horse : public Piece
	{
	public:
		Horse(Enums::Colour colour, Point position) : Piece(colour, position) {};

		Piece* Copy() override { return (Piece*) new Horse(*this); }
		Enums::PieceType GetType() const override { return Enums::HORSE; }
	};
}

#endif // !CHESS_MODEL_Horse