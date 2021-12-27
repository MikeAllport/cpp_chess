#ifndef CHESSENGINE_GAME
#define CHESSENGINE_GAME

#include "Board.h"
#include "Player.h"
#include "Move.h"
#include "Point.h"
#include "../utils/VectorHelper.h"
#include "../controller/MoveController.h"
#include "../controller/BoardController.h"
#include "../controller/MoveTikrintojas.h"

// forward ref controller
namespace ChessEngine::Controller
{
    class GameController;
}
namespace ChessEngine::Model
{
    class Game
    {
    public:
        Game(const Player& p1, const Player& p2):
            m_playersTurn(Enums::WHITE), p1(p1), p2(p2)
        { }

        friend class Controller::GameController;
        Board m_board;
    private:
        Enums::Colour m_playersTurn;
        Player p1;
        Player p2;
    };
};

#endif