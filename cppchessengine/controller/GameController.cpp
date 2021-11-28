#include "GameController.h"

namespace ChessEngine::Controller
{
    GameController::GameController(Model::Game& game, Model::Enums::MoveCheckType moveChecktype):
        m_game(game),
        c_board(m_game.m_board, m_game.p1),
        c_moveCheck(nullptr),
        c_move(nullptr) 
    {
        InitialiseControllers(moveChecktype  == Model::Enums::STANDARD? true: false);
    }

    void GameController::InitialiseControllers(bool useStandardMoveCheck)
    {
        if(useStandardMoveCheck)
        {
            c_moveCheck = new StandardMoveTikrintojas(m_game.m_board, c_board);
        }
        else
        {
            c_moveCheck = new DadsMoveTikrintojas(m_game.m_board, c_board);
        }
        c_move = new MoveController(m_game.m_board, *c_moveCheck, m_game.p1);
    }

    GameController::~GameController()
    {
        delete c_moveCheck, c_move;
    }

    GameController::GameController(const GameController& other):
        m_game(other.m_game),
        c_board(m_game.m_board, m_game.p1),
        c_moveCheck(nullptr),
        c_move(nullptr) 
    {
        InitialiseControllers(dynamic_cast<StandardMoveTikrintojas*>(other.c_moveCheck)? true: false);
    }

    GameController& GameController::operator=(const GameController& other)
    {
        m_game = other.m_game;
        InitialiseControllers(dynamic_cast<StandardMoveTikrintojas*>(other.c_moveCheck)? true: false);
        return *this;
    }

    void GameController::InitialiseGame()
    {
        m_game.m_playersTurn = Model::Enums::WHITE;
        c_board.InitialiseBoard();
    }

    void GameController::TakeTurn(const Model::Move& move)
    {
        c_board.MakeMove(move);
        m_game.m_playersTurn = m_game.m_playersTurn == Model::Enums::WHITE? Model::Enums::BLACK: Model::Enums::WHITE;
    }

    bool GameController::IsGameOver()
    {
        return c_move->GetAllColoursMoves(m_game.m_playersTurn).empty();
    }

    const Model::Player GameController::GetWinner() const
    {
        if (m_game.m_playersTurn == Model::Enums::WHITE)
        {
            return m_game.p1.IsWhite()? m_game.p2: m_game.p1;
        }
        else
        {
            return m_game.p1.IsWhite()? m_game.p1: m_game.p2;
        }
    }

    std::map<ChessEngine::Model::Point, VectorHelper<ChessEngine::Model::Move>> GameController::GetActivePlayersMoves()
    {
        return c_move->GetAllColoursMoves(m_game.m_playersTurn);
    }
}