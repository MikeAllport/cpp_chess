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
    ~BoardTest(){ }

    Chess::Model::Pawn* pawn;
    Chess::Model::Player player;
    Chess::Model::Board m_board;
    Chess::Controller::BoardController c_board;
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

TEST(BoardController, CastlingLeftWorks)
{
    BoardTest test;
    auto white = Chess::Model::Enums::WHITE;
    auto black = Chess::Model::Enums::BLACK;
    auto whiteKing = new Chess::Model::King(white, Chess::Model::Point(4, 7));
    auto whiteLeftCastle = new Chess::Model::Castle(white, Chess::Model::Point(0,7));
    auto blackLeftCastle = new Chess::Model::Castle(black, Chess::Model::Point(0,0));
    auto blackKing = new Chess::Model::King(black, Chess::Model::Point(4, 0));
    test.c_board.AddPiece({whiteKing, blackKing, whiteLeftCastle, blackLeftCastle});
    test.c_board.MakeMove(Chess::Model::Move(whiteKing->GetPosition(), Chess::Model::Point(2, 7), false));
    test.c_board.MakeMove(Chess::Model::Move(blackKing->GetPosition(), Chess::Model::Point(2, 0), false));
    auto whiteCastle = test.c_board.GetPieceSafe(3, 7);
    auto blackCastle = test.c_board.GetPieceSafe(3, 0);
    EXPECT_TRUE(whiteCastle->GetType() == Chess::Model::Enums::CASTLE);
    EXPECT_TRUE(blackCastle->GetType() == Chess::Model::Enums::CASTLE);
};


TEST(BoardController, CastlingRightWorks)
{
    BoardTest test;
    auto white = Chess::Model::Enums::WHITE;
    auto black = Chess::Model::Enums::BLACK;
    auto whiteKing = new Chess::Model::King(white, Chess::Model::Point(4, 7));
    auto whiteRightCastle = new Chess::Model::Castle(black, Chess::Model::Point(7,7));
    auto blackRightCastle = new Chess::Model::Castle(white, Chess::Model::Point(7,0));
    auto blackKing = new Chess::Model::King(black, Chess::Model::Point(4, 0));
    test.c_board.AddPiece({whiteKing, blackKing, blackRightCastle, whiteRightCastle});
    test.c_board.MakeMove(Chess::Model::Move(whiteKing->GetPosition(), Chess::Model::Point(6, 7), false));
    test.c_board.MakeMove(Chess::Model::Move(blackKing->GetPosition(), Chess::Model::Point(6, 0), false));
    auto whiteCastle = test.c_board.GetPieceSafe(5, 7);
    auto blackCastle = test.c_board.GetPieceSafe(5, 0);
    EXPECT_TRUE(whiteCastle->GetType() == Chess::Model::Enums::CASTLE);
    EXPECT_TRUE(blackCastle->GetType() == Chess::Model::Enums::CASTLE);
};

#endif