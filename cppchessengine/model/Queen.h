#ifndef CHESS_MODEL_QUEEN
#define CHESS_MODEL_QUEEN

#include "Piece.h"

namespace ChessEngine::Model
{
	class Queen : public Piece
	{
	public:
		Queen(Enums::Colour colour, Point position) : Piece(colour, position) {};

		Piece* Copy() override { return (Piece*) new Queen(*this); }
		Enums::PieceType GetType() const override { return Enums::QUEEN; }
	};
}

#endif // !CHESS_MODEL_Queen