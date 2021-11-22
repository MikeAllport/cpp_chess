#ifndef CHESS_TEST_GAME_CONTROLLER
#define CHESS_TEST_GAME_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchessengine/controller/GameController.h"
#include "../cppchessengine/controller/StandardMoveTikrintojas.h"
#include "../cppchessengine/model/Player.h"

class TestGame
{
public:
    TestGame(const ChessEngine::Model::Player& p1, const ChessEngine::Model::Player& p2):
        p1(p1), p2(p2),
        m_game(p1, p2),
        c_game(m_game, ChessEngine::Model::Enums::STANDARD)
    {}
    ~TestGame() { }
    const ChessEngine::Model::Player& p1, p2;
    ChessEngine::Model::Game m_game;
    ChessEngine::Controller::GameController c_game;
};



#endif