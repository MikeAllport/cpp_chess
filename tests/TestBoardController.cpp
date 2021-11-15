#ifndef CHESS_TEST_BOARD_CONTROLLER
#define CHESS_TEST_BOARD_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchess/controller/MoveController.h"
#include "../cppchess/controller/BoardController.h"
#include "../cppchess/model/AllPiecesInclude.h"
#include "../cppchess/model/Piece.h"
#include "../cppchess/model/Pawn.h"
#include "../cppchess/model/Point.h"

class BoardTest
{
public:
    BoardTest() : m_board(),
    player(Chess::Model::Enums::P1, Chess::Model::Enums::WHITE),
    c_board(m_board, player), 
    pawn(new Chess::Model::Pawn(Chess::Model::Enums::WHITE, Chess::Model::Point(0, 0))) {
        c_board.PlacePiece(pawn, pawn->GetPosition());
    }
    ~BoardTest(){ delete pawn;}

    Chess::Model::Pawn* pawn;
    Chess::Model::Player player;
    Chess::Controller::BoardController c_board;
    Chess::Model::Board m_board;
};

TEST(BoardController, TakesPiece)
{
    BoardTest test;
    EXPECT_TRUE(test.c_board.TakePiece(Chess::Model::Point(0, 0))->IsWhite());
};

TEST(BoardController, MovesPieceEmpty)
{
    BoardTest test;
    Chess::Model::Point from(0, 0);
    Chess::Model::Point to(0, 1);
    test.c_board.MakeMove(Chess::Model::Move(from, to, false));
    EXPECT_TRUE(test.c_board.TakePiece(to)->IsWhite());
    EXPECT_TRUE(test.c_board.TakePiece(to) == nullptr);
    EXPECT_TRUE(test.c_board.TakePiece(from) == nullptr);
};

TEST(BoardController, AttacksPiece)
{
    BoardTest test;
    auto otherPiece = new Chess::Model::Castle(Chess::Model::Enums::BLACK, Chess::Model::Point(1,1));
    test.c_board.PlacePiece(otherPiece, otherPiece->GetPosition());
    Chess::Model::Point to(1, 1);
    Chess::Model::Move move(test.pawn->GetPosition(), to, true);
    test.c_board.MakeMove(move);
    EXPECT_TRUE(test.m_board(to) == test.pawn);
    EXPECT_TRUE(test.pawn->GetPosition() == to);
    EXPECT_TRUE(test.c_board.TakePiece(Chess::Model::Point(0, 0)) == nullptr);
}

#endif