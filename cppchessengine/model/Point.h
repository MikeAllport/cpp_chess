#ifndef CHESS_MODEL_COORD
#define CHESS_MODEL_COORD

#include <iostream>

namespace ChessEngine::Model
{
	class Point
	{
	public:
		Point(int x, int y) : posX(x), posY(y) {};
		void Move(int x, int y) { posX = x; posY = y; };
		int GetX() const { return posX; };
		int GetY() const { return posY; };
		friend bool operator==(const Point &first, const Point &second) { 
			return first.GetX() == second.GetX() && first.GetY() == second.GetY();
		};
		friend bool operator<(const Point& lhs, const Point& rhs) {
			return lhs.GetY() < rhs.GetY()? lhs.GetX() < rhs.GetX(): false;
		}
		friend std::ostream &operator<<(std::ostream &os, Point const &m) { 
			return os << "Point PosX: " << m.posX << " PosY: " << m.posY;
		}
	private:
		int posX;
		int posY;
	};
}
#endif // !CHESS_MODEL_COORD