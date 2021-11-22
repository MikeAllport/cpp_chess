#ifndef CHESS_TEST_BOARD_CONTROLLER
#define CHESS_TEST_BOARD_CONTROLLER

#include <gtest/gtest.h>
#define _ALLOW_KEYWORD_MACROS
#define private public
#define protected public
#include "../cppchess/controller/MoveController.h"
#include "../cppchess/controller/BoardController.h"
#include "../cppchess/model/AllPiecesInclude.h"
#include "../cppchess/model/Piece.h"
#include "../cppchess/model/Pawn.h"
#include "../cppchess/model/Point.h"

class BoardTest
{
public:
    BoardTest(Chess::Model::Enums::Colour colour = Chess::Model::Enums::WHITE) : m_board(),
    player(Chess::Model::Enums::P1, colour),
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

TEST(BoardController, InitialiseP1White)
{
    BoardTest test;
    test.c_board.InitialiseBoard();
    for(int i = 0; i < 7; ++i)
    {
        auto blackPawn = test.c_board.GetPieceSafe(i, 1);
        auto whitePawn = test.c_board.GetPieceSafe(i, 6);
        EXPECT_TRUE(blackPawn->IsWhite() == false && blackPawn->GetType() == Chess::Model::Enums::PAWN);
        EXPECT_TRUE(whitePawn->IsWhite() == true && blackPawn->GetType() == Chess::Model::Enums::PAWN);
    }
    auto blackLeftCastle = test.c_board.GetPieceSafe(0,0);
    auto blackRightCastle = test.c_board.GetPieceSafe(7, 0);
    auto castle = Chess::Model::Enums::CASTLE;
    auto horse = Chess::Model::Enums::HORSE;
    auto bishop = Chess::Model::Enums::BISHOP;
    auto queen = Chess::Model::Enums::QUEEN;
    auto king = Chess::Model::Enums::KING;
    auto whiteLeftCastle = test.c_board.GetPieceSafe(0,7);
    auto whiteRightCastle = test.c_board.GetPieceSafe(7,7);
    auto blackLeftHorse = test.c_board.GetPieceSafe(1,0);
    auto blackRightHorse = test.c_board.GetPieceSafe(6,0);
    auto whiteLeftHorse = test.c_board.GetPieceSafe(1,7);
    auto whiteRightHorse = test.c_board.GetPieceSafe(6,7);
    auto blackLeftBishop = test.c_board.GetPieceSafe(2,0);
    auto blackRightBishop = test.c_board.GetPieceSafe(5,0);
    auto whiteLeftBishop = test.c_board.GetPieceSafe(2,7);
    auto whiteRightBishop = test.c_board.GetPieceSafe(5,7);
    auto blackQueen = test.c_board.GetPieceSafe(3, 0);
    auto blackKing = test.c_board.GetPieceSafe(4,0);
    auto whiteQueen = test.c_board.GetPieceSafe(3,7);
    auto whiteKing = test.c_board.GetPieceSafe(4,7);
    EXPECT_TRUE(blackLeftCastle->IsWhite() == false && blackLeftCastle->GetType() == castle);
    EXPECT_TRUE(blackRightCastle->IsWhite() == false && blackLeftCastle->GetType() == castle);
    EXPECT_TRUE(blackLeftHorse->IsWhite() == false && blackLeftHorse->GetType() == horse);
    EXPECT_TRUE(blackRightHorse->IsWhite() == false && blackRightHorse->GetType() == horse);
    EXPECT_TRUE(blackLeftBishop->IsWhite() == false && blackLeftBishop->GetType() == bishop);
    EXPECT_TRUE(blackRightBishop->IsWhite() == false && blackRightBishop->GetType() == bishop);
    EXPECT_TRUE(blackQueen->IsWhite() == false && blackQueen->GetType() == queen);
    EXPECT_TRUE(blackKing->IsWhite() == false && blackKing->GetType() == king);
    
    EXPECT_TRUE(whiteLeftCastle->IsWhite() == true && whiteLeftCastle->GetType() == castle);
    EXPECT_TRUE(whiteRightCastle->IsWhite() == true && whiteRightCastle->GetType() == castle);
    EXPECT_TRUE(whiteLeftHorse->IsWhite() == true && whiteLeftHorse->GetType() == horse);
    EXPECT_TRUE(whiteRightHorse->IsWhite() == true && whiteRightHorse->GetType() == horse);
    EXPECT_TRUE(whiteLeftBishop->IsWhite() == true && whiteLeftBishop->GetType() == bishop);
    EXPECT_TRUE(whiteRightBishop->IsWhite() == true && whiteRightBishop->GetType() == bishop);
    EXPECT_TRUE(whiteQueen->IsWhite() == true && whiteQueen->GetType() == queen);
    EXPECT_TRUE(whiteKing->IsWhite() == true && whiteKing->GetType() == king);
}

TEST(BoardController, IntialisesP1Black)
{
    // the black/white names in this test should be inverted, ceebs to re-type
    BoardTest test(Chess::Model::Enums::BLACK);
    test.c_board.InitialiseBoard();
    for(int i = 0; i < 7; ++i)
    {
        auto blackPawn = test.c_board.GetPieceSafe(i, 1);
        auto whitePawn = test.c_board.GetPieceSafe(i, 6);
        EXPECT_TRUE(blackPawn->IsWhite() == true && blackPawn->GetType() == Chess::Model::Enums::PAWN);
        EXPECT_TRUE(whitePawn->IsWhite() == false && blackPawn->GetType() == Chess::Model::Enums::PAWN);
    }
    auto blackLeftCastle = test.c_board.GetPieceSafe(0,0);
    auto blackRightCastle = test.c_board.GetPieceSafe(7, 0);
    auto castle = Chess::Model::Enums::CASTLE;
    auto horse = Chess::Model::Enums::HORSE;
    auto bishop = Chess::Model::Enums::BISHOP;
    auto queen = Chess::Model::Enums::QUEEN;
    auto king = Chess::Model::Enums::KING;
    auto whiteLeftCastle = test.c_board.GetPieceSafe(0,7);
    auto whiteRightCastle = test.c_board.GetPieceSafe(7,7);
    auto blackLeftHorse = test.c_board.GetPieceSafe(1,0);
    auto blackRightHorse = test.c_board.GetPieceSafe(6,0);
    auto whiteLeftHorse = test.c_board.GetPieceSafe(1,7);
    auto whiteRightHorse = test.c_board.GetPieceSafe(6,7);
    auto blackLeftBishop = test.c_board.GetPieceSafe(2,0);
    auto blackRightBishop = test.c_board.GetPieceSafe(5,0);
    auto whiteLeftBishop = test.c_board.GetPieceSafe(2,7);
    auto whiteRightBishop = test.c_board.GetPieceSafe(5,7);
    auto blackQueen = test.c_board.GetPieceSafe(3, 0);
    auto blackKing = test.c_board.GetPieceSafe(4,0);
    auto whiteQueen = test.c_board.GetPieceSafe(3,7);
    auto whiteKing = test.c_board.GetPieceSafe(4,7);
    EXPECT_TRUE(blackLeftCastle->IsWhite() == true && blackLeftCastle->GetType() == castle);
    EXPECT_TRUE(blackRightCastle->IsWhite() == true && blackLeftCastle->GetType() == castle);
    EXPECT_TRUE(blackLeftHorse->IsWhite() == true && blackLeftHorse->GetType() == horse);
    EXPECT_TRUE(blackRightHorse->IsWhite() == true && blackRightHorse->GetType() == horse);
    EXPECT_TRUE(blackLeftBishop->IsWhite() == true && blackLeftBishop->GetType() == bishop);
    EXPECT_TRUE(blackRightBishop->IsWhite() == true && blackRightBishop->GetType() == bishop);
    EXPECT_TRUE(blackQueen->IsWhite() == true && blackQueen->GetType() == queen);
    EXPECT_TRUE(blackKing->IsWhite() == true && blackKing->GetType() == king);
    
    EXPECT_TRUE(whiteLeftCastle->IsWhite() == false && whiteLeftCastle->GetType() == castle);
    EXPECT_TRUE(whiteRightCastle->IsWhite() == false && whiteRightCastle->GetType() == castle);
    EXPECT_TRUE(whiteLeftHorse->IsWhite() == false && whiteLeftHorse->GetType() == horse);
    EXPECT_TRUE(whiteRightHorse->IsWhite() == false && whiteRightHorse->GetType() == horse);
    EXPECT_TRUE(whiteLeftBishop->IsWhite() == false && whiteLeftBishop->GetType() == bishop);
    EXPECT_TRUE(whiteRightBishop->IsWhite() == false && whiteRightBishop->GetType() == bishop);
    EXPECT_TRUE(whiteQueen->IsWhite() == false && whiteQueen->GetType() == queen);
    EXPECT_TRUE(whiteKing->IsWhite() == false && whiteKing->GetType() == king);
}

#endif