#ifndef CPPCHESS_TEST
#define CPPCHESS_TEST

#include <gtest/gtest.h>
#include "../../chess/BoardEvaluator.h"

using namespace ChessEngine::Model;

TEST(ChessBoardEvaluator, WhiteP1WhitePawnY0X1Standard)
{
    Pawn piece(ChessEngine::Model::Enums::WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(ChessEngine::Model::Enums::WHITE, &piece);
    EXPECT_EQ(100, worth);
}

TEST(ChessBoardEvaluator, WhiteP1BlackPawnY1X1Standard)
{
    Pawn piece(ChessEngine::Model::Enums::BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(ChessEngine::Model::Enums::WHITE, &piece);
    EXPECT_EQ(10, worth);
}

TEST(ChessBoardEvaluator, BlackP1WhitePawnY0X1Standard)
{
    Pawn piece(ChessEngine::Model::Enums::WHITE, Point(1,0));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(ChessEngine::Model::Enums::BLACK, &piece);
    EXPECT_EQ(0, worth);
}

TEST(ChessBoardEvaluator, BlackP1BlackPawnY1X1Standard)
{
    Pawn piece(ChessEngine::Model::Enums::BLACK, Point(1,1));
    auto worth = Chess::BoardEvaluator::GetPiecePositionalScore(ChessEngine::Model::Enums::BLACK, &piece);
    EXPECT_EQ(75, worth);
}
#endif