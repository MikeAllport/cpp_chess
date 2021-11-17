#ifndef CHESS_TEST_StandardTikrintojas_CONTROLLER
#define CHESS_TEST_StandardTikrintojas_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchess/controller/MoveController.h"
#include "../cppchess/controller/BoardController.h"
#include "../cppchess/controller/StandardMoveTikrintojas.h"
#include "../cppchess/model/AllPiecesInclude.h"
#include "../cppchess/model/Piece.h"
#include "../cppchess/model/Pawn.h"
#include "../cppchess/model/Point.h"

class StandardMoveTikrintojasTest
{
public:
    StandardMoveTikrintojasTest() :  board(), 
        player(Chess::Model::Enums::P1, Chess::Model::Enums::WHITE),
        c_board(board, player),
        c_movecheck(new Chess::Controller::StandardMoveTikrintojas(board, c_board)),
        c_move(board, *c_movecheck, player) { }
        Chess::Model::Board board;
        Chess::Model::Player player;
        Chess::Controller::BoardController c_board;
        Chess::Controller::MoveTikrintojas* c_movecheck;
        Chess::Controller::MoveController c_move;
};


TEST(StandardTikrintojas, KingCheckMate)
{
    StandardMoveTikrintojasTest test;
    
    Chess::Model::Piece* blackKing = new Chess::Model::King(Chess::Model::Enums::BLACK, Chess::Model::Point(2, 0));
    Chess::Model::Piece* whiteKing = new Chess::Model::King(Chess::Model::Enums::WHITE, Chess::Model::Point(2, 2));
    Chess::Model::Piece* whiteCastle = new Chess::Model::Castle(Chess::Model::Enums::WHITE, Chess::Model::Point(6, 0));
    test.c_board.AddPiece(blackKing);
    test.c_board.AddPiece(whiteCastle);
    test.c_board.AddPiece(whiteKing);
    auto moves = test.c_move.GetValidMoves(blackKing);
    EXPECT_TRUE(moves.v.size() == 0);
};

TEST(StandardTikrintojas, PiecePutsKingInCheck)
{
    StandardMoveTikrintojasTest test;
    Chess::Model::Piece* blackQueen = new Chess::Model::Queen(Chess::Model::Enums::BLACK, Chess::Model::Point(7,0));
    Chess::Model::Piece* whitePawn = new Chess::Model::Pawn(Chess::Model::Enums::WHITE, Chess::Model::Point(7,1));
    Chess::Model::Piece* whiteKing = new Chess::Model::King(Chess::Model::Enums::WHITE, Chess::Model::Point(7,2));
    test.c_board.AddPiece(blackQueen);
    test.c_board.AddPiece(whitePawn);
    test.c_board.AddPiece(whiteKing);
    auto pawnMoves = test.c_move.GetValidMoves(whitePawn);
    auto kingMoves = test.c_move.GetValidMoves(whiteKing);
    EXPECT_TRUE(pawnMoves.v.size() == 0);
    EXPECT_TRUE(kingMoves.v.size() == 3);
};

TEST(StandardTikrintojas, KingMoveOutOfCheckSomeBlockedCastleQueenCanTakeAttacker)
{
    StandardMoveTikrintojasTest test;
    Chess::Model::Piece* blackHorse = new Chess::Model::Horse(Chess::Model::Enums::BLACK, Chess::Model::Point(5,0));
    Chess::Model::Piece* blackCastle = new Chess::Model::Castle(Chess::Model::Enums::BLACK, Chess::Model::Point(0,2));
    Chess::Model::Piece* whiteKing = new Chess::Model::King(Chess::Model::Enums::WHITE, Chess::Model::Point(7,1));
    Chess::Model::Piece* whiteQueen = new Chess::Model::Queen(Chess::Model::Enums::WHITE, Chess::Model::Point(5, 7));
    test.c_board.AddPiece(blackHorse);
    test.c_board.AddPiece(blackCastle);
    test.c_board.AddPiece(whiteKing);
    test.c_board.AddPiece(whiteQueen);
    auto kingMoves = test.c_move.GetValidMoves(whiteKing);
    auto queenMoves = test.c_move.GetValidMoves(whiteQueen);
    EXPECT_TRUE(kingMoves.v.size() == 3);
    EXPECT_TRUE(queenMoves.v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](Chess::Model::Move move) { return move.ToPosition() == Chess::Model::Point(7,0); }).v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](Chess::Model::Move move) { return move.ToPosition() == Chess::Model::Point(6,1); }).v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](Chess::Model::Move move) { return move.ToPosition() == Chess::Model::Point(6,0); }).v.size() == 1);
}

#endif