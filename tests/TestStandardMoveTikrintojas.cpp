#ifndef CHESS_TEST_StandardTikrintojas_CONTROLLER
#define CHESS_TEST_StandardTikrintojas_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchessengine/controller/MoveController.h"
#include "../cppchessengine/controller/BoardController.h"
#include "../cppchessengine/controller/StandardMoveTikrintojas.h"
#include "../cppchessengine/model/AllPiecesInclude.h"
#include "../cppchessengine/model/Piece.h"
#include "../cppchessengine/model/Pawn.h"
#include "../cppchessengine/model/Point.h"

class StandardMoveTikrintojasTest
{
public:
    StandardMoveTikrintojasTest() :  board(), 
        player(ChessEngine::Model::Enums::P1, ChessEngine::Model::Enums::WHITE),
        c_board(board, player),
        c_movecheck(new ChessEngine::Controller::StandardMoveTikrintojas(board, c_board)),
        c_move(board, *c_movecheck, player) { }
        ChessEngine::Model::Board board;
        ChessEngine::Model::Player player;
        ChessEngine::Controller::BoardController c_board;
        ChessEngine::Controller::MoveTikrintojas* c_movecheck;
        ChessEngine::Controller::MoveController c_move;
};


TEST(StandardTikrintojas, KingCheckMate)
{
    StandardMoveTikrintojasTest test;
    
    ChessEngine::Model::Piece* blackKing = new ChessEngine::Model::King(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(2, 0));
    ChessEngine::Model::Piece* whiteKing = new ChessEngine::Model::King(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(2, 2));
    ChessEngine::Model::Piece* whiteCastle = new ChessEngine::Model::Castle(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(6, 0));
    test.c_board.AddPiece(blackKing);
    test.c_board.AddPiece(whiteCastle);
    test.c_board.AddPiece(whiteKing);
    auto moves = test.c_move.GetValidMoves(blackKing);
    EXPECT_TRUE(moves.v.size() == 0);
};

TEST(StandardTikrintojas, PiecePutsKingInCheck)
{
    StandardMoveTikrintojasTest test;
    ChessEngine::Model::Piece* blackQueen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(7,0));
    ChessEngine::Model::Piece* whitePawn = new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(7,1));
    ChessEngine::Model::Piece* whiteKing = new ChessEngine::Model::King(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(7,2));
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
    ChessEngine::Model::Piece* blackHorse = new ChessEngine::Model::Horse(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(5,0));
    ChessEngine::Model::Piece* blackCastle = new ChessEngine::Model::Castle(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(0,2));
    ChessEngine::Model::Piece* whiteKing = new ChessEngine::Model::King(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(7,1));
    ChessEngine::Model::Piece* whiteQueen = new ChessEngine::Model::Queen(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(5, 7));
    test.c_board.AddPiece(blackHorse);
    test.c_board.AddPiece(blackCastle);
    test.c_board.AddPiece(whiteKing);
    test.c_board.AddPiece(whiteQueen);
    auto kingMoves = test.c_move.GetValidMoves(whiteKing);
    auto queenMoves = test.c_move.GetValidMoves(whiteQueen);
    EXPECT_TRUE(kingMoves.v.size() == 3);
    EXPECT_TRUE(queenMoves.v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](ChessEngine::Model::Move move) { return move.ToPosition() == ChessEngine::Model::Point(7,0); }).v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](ChessEngine::Model::Move move) { return move.ToPosition() == ChessEngine::Model::Point(6,1); }).v.size() == 1);
    EXPECT_TRUE(kingMoves.Filter([](ChessEngine::Model::Move move) { return move.ToPosition() == ChessEngine::Model::Point(6,0); }).v.size() == 1);
}

#endif