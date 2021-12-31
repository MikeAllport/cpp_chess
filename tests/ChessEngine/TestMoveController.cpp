#ifndef CHESS_TEST_MOVE_CONTROLLER
#define CHESS_TEST_MOVE_CONTROLLER

#include <gtest/gtest.h>
#define _ALLOW_KEYWORD_MACROS
#define private public
#define protected public
#include "../../cppchessengine/controller/BoardController.h"
#include "../../cppchessengine/controller/MoveController.h"
#include "../../cppchessengine/controller/StandardMoveTikrintojas.h"
#include "../../cppchessengine/model/AllPiecesInclude.h"
#include "../../cppchessengine/model/Piece.h"
#include "../../cppchessengine/model/Pawn.h"
#include "../../cppchessengine/model/Point.h"

class MoveControllerTest
{
public:
    MoveControllerTest() :  board(), 
        pawn(new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(1, 0))),
        player(ChessEngine::Model::Enums::P1, ChessEngine::Model::Enums::WHITE),
        c_board(board, player), 
        c_movecheck(new ChessEngine::Controller::StandardMoveTikrintojas(board, c_board)),
        c_move(board, *c_movecheck, player) { c_board.PlacePiece(pawn, pawn->GetPosition());}
        ChessEngine::Model::Board board;
        ChessEngine::Model::Pawn* pawn;
        ChessEngine::Model::Player player;
        ChessEngine::Controller::BoardController c_board;
        ChessEngine::Controller::MoveTikrintojas* c_movecheck;
        ChessEngine::Controller::MoveController c_move;
};

TEST(MoveController, PawnMoveForward)
{
    MoveControllerTest test;
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v.size() == 2);
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v[0].ToPosition() == ChessEngine::Model::Point(1, 1));
};

TEST(MoveController, PawnCantMoveForward)
{
    MoveControllerTest test;
    ChessEngine::Model::Point newPawnPosition(1, 1);
    ChessEngine::Model::Pawn* blockingPawn = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::BLACK, newPawnPosition);
    test.c_board.PlacePiece(blockingPawn, newPawnPosition);
    EXPECT_TRUE(test.c_move.GetMoves(test.pawn).v.size() == 0);
    ChessEngine::Model::Piece* testPiece = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::BLACK, newPawnPosition);
};


TEST(MoveController, PawnAttacks)
{
    MoveControllerTest test;
    ChessEngine::Model::Point attackFirstPos(0, 1);
    ChessEngine::Model::Point attackSecondPos(2, 1);
    ChessEngine::Model::Pawn* takenPawn1 = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::WHITE, attackFirstPos);
    ChessEngine::Model::Pawn* takenPawn2 = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::WHITE, attackSecondPos);
    test.c_board.PlacePiece(takenPawn1, attackFirstPos);
    test.c_board.PlacePiece(takenPawn1, attackSecondPos);
    auto moves = test.c_move.GetMoves(test.pawn);
    ChessEngine::Model::Point origin(1, 0);
    EXPECT_TRUE(moves.v.size() == 4);
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(origin, attackSecondPos, true)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(origin, attackFirstPos, true)));
}

TEST(MoveController, UpgradesPawnWhite)
{
    MoveControllerTest test;
    auto pawn = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(1,1));
    test.c_board.AddPiece(pawn);
    EXPECT_TRUE(test.board(1, 1) == pawn);
    test.c_board.MakeMove(ChessEngine::Model::Move(pawn->GetPosition(), ChessEngine::Model::Point(1,0), false));
    EXPECT_FALSE(test.board(1,0) == pawn);
    EXPECT_TRUE(test.board(1,0)->GetType() == ChessEngine::Model::Enums::QUEEN);
    EXPECT_TRUE(test.board.ActivePieces().Contains(test.board(1,0)));
    EXPECT_FALSE(test.board.ActivePieces().Contains(pawn));
}

TEST(MoveController, GetsDiagonalsQueen)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(ChessEngine::Model::Point(1, 0));
    auto position = ChessEngine::Model::Point(4, 4);
    auto queen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::BLACK, position);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(1, 1), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(7, 1), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(1, 7), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(7, 7), false)));
}

TEST(MoveController, GetsHorizontalsQueen)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(ChessEngine::Model::Point(1, 0));
    auto position = ChessEngine::Model::Point(4, 4);
    auto queen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::BLACK, position);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(4, 0), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(4, 7), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(0, 4), false)));
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(7, 4), false)));
}

TEST(MoveController, QueenCantMovePastAttack)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(ChessEngine::Model::Point(1, 0));
    auto position = ChessEngine::Model::Point(4, 4);
    auto queen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::BLACK, position);
    pawn->MoveTo(ChessEngine::Model::Point(3, 3));
    test.c_board.AddPiece(pawn);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_FALSE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(2, 2), false)));
}

TEST(MoveController, QueenCanAttack)
{
    MoveControllerTest test;
    auto pawn = test.c_board.TakePiece(ChessEngine::Model::Point(1, 0));
    auto position = ChessEngine::Model::Point(4, 4);
    auto queen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::WHITE, position);
    pawn->MoveTo(ChessEngine::Model::Point(3, 3));
    test.c_board.AddPiece(pawn);
    auto moves = test.c_move.GetMoves(queen);
    EXPECT_TRUE(moves.Contains(ChessEngine::Model::Move(queen->GetPosition(), ChessEngine::Model::Point(3, 3), true)));
}

TEST(MoveController, GetsCatlingPositions)
{
    MoveControllerTest test;
    auto white = ChessEngine::Model::Enums::WHITE;
    auto king = new ChessEngine::Model::King(white, ChessEngine::Model::Point(4, 7));
    auto leftCastle = new ChessEngine::Model::Castle(white, ChessEngine::Model::Point(0,7));
    auto rightCastle = new ChessEngine::Model::Castle(white, ChessEngine::Model::Point(7,7));
    test.c_board.AddPiece({king, leftCastle, rightCastle});
    auto moves = test.c_move.GetMoves(king);
    EXPECT_TRUE(moves.Filter([king](ChessEngine::Model::Move move) { 
        return move.ToPosition() == ChessEngine::Model::Point(2, 7); 
        }).v.size() == 1);
    EXPECT_TRUE(moves.Filter([king](ChessEngine::Model::Move move) { 
        return move.ToPosition() == ChessEngine::Model::Point(6, 7); 
        }).v.size() == 1);
}

#endif