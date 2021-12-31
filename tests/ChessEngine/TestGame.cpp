#ifndef CHESS_TEST_GAME_CONTROLLER
#define CHESS_TEST_GAME_CONTROLLER

#include <gtest/gtest.h>
#define _ALLOW_KEYWORD_MACROS
#define private public
#define protected public
#include "../../cppchessengine/controller/GameController.h"
#include "../../cppchessengine/controller/StandardMoveTikrintojas.h"
#include "../../cppchessengine/model/Player.h"

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

TEST(Game, WhiteP1BlackP2WhiteBeatsBlack)
{
    auto p1 = ChessEngine::Model::Enums::P1;
    auto p2 = ChessEngine::Model::Enums::P2;
    auto white = ChessEngine::Model::Enums::WHITE;
    auto black = ChessEngine::Model::Enums::BLACK;
    auto player1 = ChessEngine::Model::Player(p1, white);
    const ChessEngine::Model::Player player2(p2, black);
    TestGame game(player1, player2);
    game.c_game.InitialiseGame();

    auto moves = game.c_game.GetActivePlayersMoves();
    EXPECT_TRUE(moves.size() == 10);
    game.c_game.TakeTurn(moves.find(ChessEngine::Model::Point(5, 6))->second.
        Filter([](ChessEngine::Model::Move move) { return move.ToPosition().GetY() == 5; }).v[0]);

    EXPECT_TRUE(game.c_game.IsGameOver() == false);
    EXPECT_TRUE(game.c_game.m_game.m_playersTurn == black);
    moves = game.c_game.GetActivePlayersMoves();
    EXPECT_TRUE(moves.size() == 10);
    game.c_game.TakeTurn(moves.find(ChessEngine::Model::Point(4, 1))->second.
        Filter([](ChessEngine::Model::Move move) { return move.ToPosition().GetY() == 3; }).v[0]);

    EXPECT_TRUE(game.c_game.IsGameOver() == false);
    EXPECT_TRUE(game.c_game.m_game.m_playersTurn == white);
    moves = game.c_game.GetActivePlayersMoves();
    game.c_game.TakeTurn(moves.find(ChessEngine::Model::Point(6, 6))->second.
    Filter([](ChessEngine::Model::Move move) { return move.ToPosition().GetY() == 4; }).v[0]);

    EXPECT_TRUE(game.c_game.IsGameOver() == false);
    EXPECT_TRUE(game.c_game.m_game.m_playersTurn == black);
    moves = game.c_game.GetActivePlayersMoves();
    game.c_game.TakeTurn(moves.find(ChessEngine::Model::Point(3, 0))->second.
    Filter([](ChessEngine::Model::Move move) { return move.ToPosition().GetY() == 4; }).v[0]);
    EXPECT_TRUE(game.c_game.IsGameOver() == true);
    EXPECT_TRUE(game.c_game.GetWinnersColour() == black);
}

#endif