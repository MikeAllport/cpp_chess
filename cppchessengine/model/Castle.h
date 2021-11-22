#ifndef CHESS_MODEL_CASTLE
#define CHESS_MODEL_CASTLE

#include "Piece.h"

namespace ChessEngine::Model
{
	class Castle : public Piece
	{
	public:
		Castle(Enums::Colour colour, Point position) : Piece(colour, position), hasMoved(false) {};
		Castle(const Castle& other): Piece(other), hasMoved(other.hasMoved) {};
		~Castle() override {}

		Piece* Copy() override { return (Piece*)new Castle(*this); }
		Enums::PieceType GetType() const override { return Enums::CASTLE; }
		bool HasMoved() { return hasMoved; };
		void SetMoved() { hasMoved = true; }
	private:
		bool hasMoved;
	};
}

#endif // !CHESS_MODEL_Castle