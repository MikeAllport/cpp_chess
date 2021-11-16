#ifndef CHESS_TEST_MOVE_CONTROLLER
#define CHESS_TEST_MOVE_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchess/controller/MoveController.h"
#include "../cppchess/controller/BoardController.h"
#include "../cppchess/controller/StandardMoveTikrintojas.h"
#include "../cppchess/model/AllPiecesInclude.h"
#include "../cppchess/model/Piece.h"
#include "../cppchess/model/Pawn.h"
#include "../cppchess/model/Point.h"

class MoveControllerTest
{
public:
    MoveControllerTest() :  board(), 
        pawn(new Chess::Model::Pawn(Chess::Model::Enums::BLACK, Chess::Model::Point(1, 0))),
        player(Chess::Model::Enums::P1, Chess::Model::Enums::WHITE),
        c_board(board, player), 
        c_movecheck(new Chess::Controller::StandardMoveTikrintojas(board, c_board)),
        c_move(board, Chess::Controller::StandardMoveTikrintojas(board, c_board), player) { c_board.PlacePiece(pawn, pawn->GetPosition());}
        Chess::Model::Board board;
        Chess::Model::Pawn* pawn;
        Chess::Model::Player player;
        Chess::Controller::BoardController c_board;
        Chess::Controller::MoveTikrintojas* c_movecheck;
        Chess::Controller::MoveController c_move;
};

TEST(MoveController, PawnMoveForward)
{
    MoveControllerTest test;
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v.size() == 1);
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v[0].ToPosition() == Chess::Model::Point(1, 1));
};

TEST(MoveController, PawnCantMoveForward)
{
    MoveControllerTest test;
    Chess::Model::Point newPawnPosition(1, 1);
    Chess::Model::Pawn* blockingPawn = new Chess::Model::Pawn(Chess::Model::Enums::BLACK, newPawnPosition);
    test.c_board.PlacePiece(blockingPawn, newPawnPosition);
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v.size() == 0);
    Chess::Model::Piece* testPiece = new Chess::Model::Pawn(Chess::Model::Enums::BLACK, newPawnPosition);
};


TEST(MoveController, PawnAttacks)
{
    MoveControllerTest test;
    Chess::Model::Point attackFirstPos(0, 1);
    Chess::Model::Point attackSecondPos(2, 1);
    Chess::Model::Pawn* takenPawn1 = new Chess::Model::Pawn(Chess::Model::Enums::WHITE, attackFirstPos);
    Chess::Model::Pawn* takenPawn2 = new Chess::Model::Pawn(Chess::Model::Enums::WHITE, attackSecondPos);
    test.c_board.PlacePiece(takenPawn1, attackFirstPos);
    test.c_board.PlacePiece(takenPawn1, attackSecondPos);
    auto moves = test.c_move.GetMoves(test.pawn);
    Chess::Model::Point origin(1, 0);
    EXPECT_TRUE(moves.v.size() == 3);
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(origin, attackSecondPos, true)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(origin, attackFirstPos, true)));
}

TEST(MoveController, UpgradesPawnWhite)
{
    MoveControllerTest test;
    auto pawn = new Chess::Model::Pawn(Chess::Model::Enums::WHITE, Chess::Model::Point(1,1));
    test.c_board.AddPiece(pawn);
    EXPECT_TRUE(test.board(1, 1) == pawn);
    test.c_board.MakeMove(Chess::Model::Move(pawn->GetPosition(), Chess::Model::Point(1,0), false));
    EXPECT_FALSE(test.board(1,0) == pawn);
    EXPECT_TRUE(test.board(1,0)->GetType() == Chess::Model::Enums::QUEEN);
    EXPECT_TRUE(test.board.ActivePieces().Contains(test.board(1,0)));
    EXPECT_FALSE(test.board.ActivePieces().Contains(pawn));
}

TEST(MoveController, GetsDiagonalsQueen)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(Chess::Model::Point(1, 0));
    auto position = Chess::Model::Point(4, 4);
    auto queen = new Chess::Model::Queen(Chess::Model::Enums::BLACK, position);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(1, 1), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(7, 1), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(1, 7), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(7, 7), false)));
}

TEST(MoveController, GetsHorizontalsQueen)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(Chess::Model::Point(1, 0));
    auto position = Chess::Model::Point(4, 4);
    auto queen = new Chess::Model::Queen(Chess::Model::Enums::BLACK, position);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(4, 0), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(4, 7), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(0, 4), false)));
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(7, 4), false)));
}

TEST(MoveController, QueenCantMovePastAttack)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(Chess::Model::Point(1, 0));
    auto position = Chess::Model::Point(4, 4);
    auto queen = new Chess::Model::Queen(Chess::Model::Enums::BLACK, position);
    pawn->MoveTo(Chess::Model::Point(3, 3));
    test.c_board.AddPiece(pawn);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_FALSE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(2, 2), false)));
}

TEST(MoveController, QueenCanAttack)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(Chess::Model::Point(1, 0));
    auto position = Chess::Model::Point(4, 4);
    auto queen = new Chess::Model::Queen(Chess::Model::Enums::WHITE, position);
    pawn->MoveTo(Chess::Model::Point(3, 3));
    test.c_board.AddPiece(pawn);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(Chess::Model::Move(queen->GetPosition(), Chess::Model::Point(3, 3), true)));
}

#endif