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
#include "StandardMoveTikrintojas.h"
#include "DadsMoveTikrintojas.h"

namespace ChessEngine::Controller
{
    class GameController
    {
    public:
        GameController(Model::Game& game, Model::Enums::MoveCheckType);
        GameController(const GameController& other);
        ~GameController();
        GameController& operator=(const GameController& other);
        std::map<ChessEngine::Model::Point, VectorHelper<ChessEngine::Model::Move>> GetActivePlayersMoves();
        void TakeTurn(const Model::Move& move);
        bool IsGameOver();
        const Model::Enums::Colour GetWinnersColour() const;
        void InitialiseGame();
        Model::Game& m_game;
        Controller::BoardController c_board;
        Controller::MoveController* c_move;
    private:
        void InitialiseControllers(bool useStandardMC);
        Controller::MoveTikrintojas* c_moveCheck;
    };
};

#endif