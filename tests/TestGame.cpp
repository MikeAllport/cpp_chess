#ifndef CHESS_TEST_GAME_CONTROLLER
#define CHESS_TEST_GAME_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchess/controller/GameController.h"
#include "../cppchess/controller/StandardMoveTikrintojas.h"
#include "../cppchess/model/Player.h"

class TestGame
{
public:
    TestGame(const Chess::Model::Player& p1, const Chess::Model::Player& p2):
        p1(p1), p2(p2),
        m_game(p1, p2),
        c_game(m_game, Chess::Model::Enums::STANDARD)
    {}
    ~TestGame() { }
    const Chess::Model::Player& p1, p2;
    Chess::Model::Game m_game;
    Chess::Controller::GameController c_game;
};


#endif