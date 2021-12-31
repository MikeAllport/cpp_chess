#ifndef CPPCHESS_TEST
#define CPPCHESS_TEST

#include <gtest/gtest.h>
#include "../../chess/BoardEvaluator.h"

using namespace ChessEngine::Model;

TEST(ChessBoardEvaluator, WhiteP1WhitePawnY0X1Standard)
{
    Pawn piece(WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(WHITE, STANDARD, &piece);
    EXPECT_EQ(100, worth);
}

TEST(ChessBoardEvaluator, WhiteP1BlackPawnY1X1Standard)
{
    Pawn piece(BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(WHITE, STANDARD, &piece);
    EXPECT_EQ(10, worth);
}

TEST(ChessBoardEvaluator, BlackP1WhitePawnY0X1Standard)
{
    Pawn piece(WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(BLACK, STANDARD, &piece);
    EXPECT_EQ(0, worth);
}

TEST(ChessBoardEvaluator, BlackP1BlackPawnY1X1Standard)
{
    Pawn piece(BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(BLACK, STANDARD, &piece);
    EXPECT_EQ(75, worth);
}

TEST(ChessBoardEvaluator, WhiteP1WhitePawnY0X1Dads)
{
    Pawn piece(WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(WHITE, DADS, &piece);
    EXPECT_EQ(-100, worth);
}

TEST(ChessBoardEvaluator, WhiteP1BlackPawnY1X1Dads)
{
    Pawn piece(BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(WHITE, DADS, &piece);
    EXPECT_EQ(-10, worth);
}

TEST(ChessBoardEvaluator, BlackP1WhitePawnY0X1Dads)
{
    Pawn piece(WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(BLACK, DADS, &piece);
    EXPECT_EQ(0, worth);
}

TEST(ChessBoardEvaluator, BlackP1BlackPawnY1X1Dads)
{
    Pawn piece(BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(BLACK, DADS, &piece);
    EXPECT_EQ(-75, worth);
}

#endif