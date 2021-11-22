#ifndef CHESS_TEST_BOARD_CONTROLLER
#define CHESS_TEST_BOARD_CONTROLLER

#include <gtest/gtest.h>
#define _ALLOW_KEYWORD_MACROS
#define private public
#define protected public
#include "../cppchessengine/controller/MoveController.h"
#include "../cppchessengine/controller/BoardController.h"
#include "../cppchessengine/model/AllPiecesInclude.h"
#include "../cppchessengine/model/Piece.h"
#include "../cppchessengine/model/Pawn.h"
#include "../cppchessengine/model/Point.h"

class BoardTest
{
public:
    BoardTest(ChessEngine::Model::Enums::Colour colour = ChessEngine::Model::Enums::WHITE) : m_board(),
    player(ChessEngine::Model::Enums::P1, colour),
    c_board(m_board, player), 
    pawn(new ChessEngine::Model::Pawn(ChessEngine::Model::Enums::WHITE, ChessEngine::Model::Point(0, 0))) {
        c_board.PlacePiece(pawn, pawn->GetPosition());
    }
    ~BoardTest(){ }

    ChessEngine::Model::Pawn* pawn;
    ChessEngine::Model::Player player;
    ChessEngine::Model::Board m_board;
    ChessEngine::Controller::BoardController c_board;
};

TEST(BoardController, TakesPiece)
{
    BoardTest test;
    EXPECT_TRUE(test.c_board.TakePiece(ChessEngine::Model::Point(0, 0))->IsWhite());
};

TEST(BoardController, MovesPieceEmpty)
{
    BoardTest test;
    ChessEngine::Model::Point from(0, 0);
    ChessEngine::Model::Point to(0, 1);
    test.c_board.MakeMove(ChessEngine::Model::Move(from, to, false));
    EXPECT_TRUE(test.c_board.TakePiece(to)->IsWhite());
    EXPECT_TRUE(test.c_board.TakePiece(to) == nullptr);
    EXPECT_TRUE(test.c_board.TakePiece(from) == nullptr);
};

TEST(BoardController, AttacksPiece)
{
    BoardTest test;
    auto otherPiece = new ChessEngine::Model::Castle(ChessEngine::Model::Enums::BLACK, ChessEngine::Model::Point(1,1));
    test.c_board.PlacePiece(otherPiece, otherPiece->GetPosition());
    ChessEngine::Model::Point to(1, 1);
    ChessEngine::Model::Move move(test.pawn->GetPosition(), to, true);
    test.c_board.MakeMove(move);
    EXPECT_TRUE(test.m_board(to) == test.pawn);
    EXPECT_TRUE(test.pawn->GetPosition() == to);
    EXPECT_TRUE(test.c_board.TakePiece(ChessEngine::Model::Point(0, 0)) == nullptr);
}

TEST(BoardController, CastlingLeftWorks)
{
    BoardTest test;
    auto white = ChessEngine::Model::Enums::WHITE;
    auto black = ChessEngine::Model::Enums::BLACK;
    auto whiteKing = new ChessEngine::Model::King(white, ChessEngine::Model::Point(4, 7));
    auto whiteLeftCastle = new ChessEngine::Model::Castle(white, ChessEngine::Model::Point(0,7));
    auto blackLeftCastle = new ChessEngine::Model::Castle(black, ChessEngine::Model::Point(0,0));
    auto blackKing = new ChessEngine::Model::King(black, ChessEngine::Model::Point(4, 0));
    test.c_board.AddPiece({whiteKing, blackKing, whiteLeftCastle, blackLeftCastle});
    test.c_board.MakeMove(ChessEngine::Model::Move(whiteKing->GetPosition(), ChessEngine::Model::Point(2, 7), false));
    test.c_board.MakeMove(ChessEngine::Model::Move(blackKing->GetPosition(), ChessEngine::Model::Point(2, 0), false));
    auto whiteCastle = test.c_board.GetPieceSafe(3, 7);
    auto blackCastle = test.c_board.GetPieceSafe(3, 0);
    EXPECT_TRUE(whiteCastle->GetType() == ChessEngine::Model::Enums::CASTLE);
    EXPECT_TRUE(blackCastle->GetType() == ChessEngine::Model::Enums::CASTLE);
};


TEST(BoardController, CastlingRightWorks)
{
    BoardTest test;
    auto white = ChessEngine::Model::Enums::WHITE;
    auto black = ChessEngine::Model::Enums::BLACK;
    auto whiteKing = new ChessEngine::Model::King(white, ChessEngine::Model::Point(4, 7));
    auto whiteRightCastle = new ChessEngine::Model::Castle(black, ChessEngine::Model::Point(7,7));
    auto blackRightCastle = new ChessEngine::Model::Castle(white, ChessEngine::Model::Point(7,0));
    auto blackKing = new ChessEngine::Model::King(black, ChessEngine::Model::Point(4, 0));
    test.c_board.AddPiece({whiteKing, blackKing, blackRightCastle, whiteRightCastle});
    test.c_board.MakeMove(ChessEngine::Model::Move(whiteKing->GetPosition(), ChessEngine::Model::Point(6, 7), false));
    test.c_board.MakeMove(ChessEngine::Model::Move(blackKing->GetPosition(), ChessEngine::Model::Point(6, 0), false));
    auto whiteCastle = test.c_board.GetPieceSafe(5, 7);
    auto blackCastle = test.c_board.GetPieceSafe(5, 0);
    EXPECT_TRUE(whiteCastle->GetType() == ChessEngine::Model::Enums::CASTLE);
    EXPECT_TRUE(blackCastle->GetType() == ChessEngine::Model::Enums::CASTLE);
};

TEST(BoardController, InitialiseP1White)
{
    BoardTest test;
    test.c_board.InitialiseBoard();
    for(int i = 0; i < 7; ++i)
    {
        auto blackPawn = test.c_board.GetPieceSafe(i, 1);
        auto whitePawn = test.c_board.GetPieceSafe(i, 6);
        EXPECT_TRUE(blackPawn->IsWhite() == false && blackPawn->GetType() == ChessEngine::Model::Enums::PAWN);
        EXPECT_TRUE(whitePawn->IsWhite() == true && blackPawn->GetType() == ChessEngine::Model::Enums::PAWN);
    }
    auto blackLeftCastle = test.c_board.GetPieceSafe(0,0);
    auto blackRightCastle = test.c_board.GetPieceSafe(7, 0);
    auto castle = ChessEngine::Model::Enums::CASTLE;
    auto horse = ChessEngine::Model::Enums::HORSE;
    auto bishop = ChessEngine::Model::Enums::BISHOP;
    auto queen = ChessEngine::Model::Enums::QUEEN;
    auto king = ChessEngine::Model::Enums::KING;
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
    BoardTest test(ChessEngine::Model::Enums::BLACK);
    test.c_board.InitialiseBoard();
    for(int i = 0; i < 7; ++i)
    {
        auto blackPawn = test.c_board.GetPieceSafe(i, 1);
        auto whitePawn = test.c_board.GetPieceSafe(i, 6);
        EXPECT_TRUE(blackPawn->IsWhite() == true && blackPawn->GetType() == ChessEngine::Model::Enums::PAWN);
        EXPECT_TRUE(whitePawn->IsWhite() == false && blackPawn->GetType() == ChessEngine::Model::Enums::PAWN);
    }
    auto blackLeftCastle = test.c_board.GetPieceSafe(0,0);
    auto blackRightCastle = test.c_board.GetPieceSafe(7, 0);
    auto castle = ChessEngine::Model::Enums::CASTLE;
    auto horse = ChessEngine::Model::Enums::HORSE;
    auto bishop = ChessEngine::Model::Enums::BISHOP;
    auto queen = ChessEngine::Model::Enums::QUEEN;
    auto king = ChessEngine::Model::Enums::KING;
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