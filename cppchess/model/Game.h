#ifndef CHESS_GAME
#define CHESS_GAME

#include "Board.h"
#include "Player.h"
#include "Move.h"
#include "Point.h"
#include "../utils/VectorHelper.h"
#include "../controller/MoveController.h"
#include "../controller/BoardController.h"
#include "../controller/MoveTikrintojas.h"

namespace Chess::Model
{
    class Game
    {
    public:
        Game(const Player& p1, const Player& p2, Controller::MoveTikrintojas* c_moveCheck):
            playersTurn(Enums::WHITE), m_whitePlayer(nullptr), m_blackPlayer(nullptr), c_moveCheck(c_moveCheck)
        {
            if(p1.IsWhite())
            {
                m_whitePlayer = &p1;
                m_blackPlayer = &p2;
            }
            else
            {
                m_whitePlayer = &p2;
                m_blackPlayer = &p1;
            }
            c_board = Chess::Controller::BoardController(m_board, p1);
            c_move = Chess::Controller::MoveController(m_board, *c_moveCheck, p1);
            //TODO initialise pieces
        };

        VectorHelper<std::map<Chess::Model::Point, VectorHelper<Chess::Model::Move>>> GetActivePlayersMoves();
        void TakeTurn(const Move& move);
        bool IsGameOver();
        Player GetWinner();
        Enums::Colour playersTurn;
        const Player* m_whitePlayer;
        const Player* m_blackPlayer;
        Board m_board;
        Controller::BoardController c_board;
        Controller::MoveTikrintojas* c_moveCheck;
        Controller::MoveController c_move;
    };
};

#endif