#ifndef MODEL_PLAYER
#define MODEL_PLAYER

#include "Enums.h"

namespace Chess::Model
{
	class Player
	{
	public:
		Player(Enums::Player player, Enums::Colour colour) : player(player), colour(colour) { }
		bool IsWhite() { return colour == Enums::WHITE; }
	private:
		Enums::Player player;
		Enums::Colour colour;
	};
}
#endif // !MODEL_PLAYER
