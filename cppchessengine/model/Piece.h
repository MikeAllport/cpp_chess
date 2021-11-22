#ifndef CHESS_MODEL_PIECE
#define CHESS_MODEL_PIECE


#include "Point.h"
#include "Enums.h"

namespace ChessEngine::Model
{
	class Piece
	{
	public:
		Piece(Enums::Colour colour, Point position) : colour(colour), coord(position) {};
		Piece(const Piece& other): colour(other.colour), coord(other.coord) {}
		virtual ~Piece() {}
		virtual Piece* Copy() = 0;
		bool IsWhite() const { return colour == Enums::Colour::WHITE; }
		Point GetPosition() const { return coord; }
		void MoveTo(Point position) { coord.Move(position.GetX(), position.GetY()); }

		// Polymorphic method to determine pieces type
		virtual Enums::PieceType GetType() const = 0;
	private:
		Piece();
		Enums::Colour colour;
		Point coord;
	};
}


#endif // !CHESS_MODEL_PIECE