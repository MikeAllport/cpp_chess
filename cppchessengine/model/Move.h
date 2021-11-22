#ifndef CHESS_MODEL_MOVE
#define CHESS_MODEL_MOVE

#include "Point.h"
#include <iostream>

namespace ChessEngine::Model
{
	class Move
	{
	public: 
		Move(Point fromPosition, Point toPosition, bool isAttack) : 
			fromPosition(fromPosition), 
			toPosition(toPosition),
			attack(isAttack) {};
		const bool IsAttack() const { return attack; };	
		Point FromPosition() const { return fromPosition; };
		Point ToPosition() const { return toPosition; };
		friend bool operator==(const Move& lhs, const Move& rhs){
			return lhs.FromPosition() == rhs.FromPosition() &&
				lhs.ToPosition() == rhs.ToPosition() &&
				lhs.IsAttack() == rhs.IsAttack();
		}
		friend std::ostream& operator<<(std::ostream& os, Move& m) {  
			return os << "Move From: " << m.FromPosition() << " Moving To: " << m.ToPosition()
			<< " IsAttacking " << (m.IsAttack()? "true": "false");
		};
	private:
		Point fromPosition;
		Point toPosition;
		bool attack;
	};
}

#endif