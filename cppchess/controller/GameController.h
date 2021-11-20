#ifndef CHESS_GAME_CONTROLLER
#define CHESS_GAME_CONTROLLER

#include "../model/Board.h"
#include "../model/Player.h"
#include "../model/Move.h"
#include "../model/Point.h"
#include "../model/Game.h"
#include "../utils/VectorHelper.h"
#include "MoveController.h"
#include "BoardController.h"
#include "MoveTikrintojas.h"

namespace Chess::Controller
{
    class GameController
    {
    public:
        GameController(const Model::Player& p1, const Model::Player& p2, MoveTikrintojas* c_moveCheck);
        VectorHelper<std::map<Chess::Model::Point, VectorHelper<Chess::Model::Move>>> GetActivePlayersMoves();
        void TakeTurn(const Model::Move& move);
        bool IsGameOver();
        const Model::Player GetWinner() const;
    private:
        void initialiseBoard(const Model::Player& p1, const Model::Player& p2);
        Model::Game m_game;
    };
};

#endif