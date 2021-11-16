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
        c_move(board, player),
        c_board(board, player),
        c_movecheck(board, c_board) { }
        Chess::Model::Board board;
        Chess::Model::Player player;
        Chess::Controller::MoveController c_move;
        Chess::Controller::BoardController c_board;
        Chess::Controller::StandardMoveTikrintojas c_movecheck;
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

#endif