#ifndef CHESS_MODEL_PAWN
#define CHESS_MODEL_PAWN

#include "Piece.h"

namespace ChessEngine::Model
{
	class Pawn : public Piece
	{
	public:
		Pawn(Enums::Colour colour, Point position) : Piece(colour, position) {};

		Piece* Copy() override { return (Piece*) new Pawn(*this); }
		Enums::PieceType GetType() const override { return Enums::PAWN; }
	};
}

#endif // !CHESS_MODEL_PAWN