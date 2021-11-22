#ifndef CHESS_TEST_StandardTikrintojas_CONTROLLER
#define CHESS_TEST_StandardTikrintojas_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchessengine/controller/MoveController.h"
#include "../cppchessengine/controller/BoardController.h"
#include "../cppchessengine/model/Board.h"
#include "../cppchessengine/model/AllPiecesInclude.h"
#include "../cppchessengine/model/Piece.h"
#include "../cppchessengine/model/Pawn.h"
#include "../cppchessengine/model/Point.h"

class TestBoard
{
public:
    TestBoard():
        board1(new ChessEngine::Model::Board()),
        player(ChessEngine::Model::Enums::P1, ChessEngine::Model::Enums::WHITE),
        c_board1(*board1, player),
        queenPosition(0,0),
        horsePosition(7,7),
        queen1(new ChessEngine::Model::Queen(ChessEngine::Model::Enums::WHITE, queenPosition)),
        horse1(new ChessEngine::Model::Horse(ChessEngine::Model::Enums::WHITE, horsePosition)) 
        {
            c_board1.AddPiece({queen1, horse1});
        }
    ~TestBoard() { delete board1; }
    ChessEngine::Model::Board* board1;
    ChessEngine::Model::Player player;
    ChessEngine::Controller::BoardController c_board1;
    ChessEngine::Model::Point queenPosition;
    ChessEngine::Model::Point horsePosition;
    ChessEngine::Model::Piece* queen1;
    ChessEngine::Model::Piece* horse1;
};

TEST(Board, CopyingBoardWorks)
{
    TestBoard test;
    // init board 2
    ChessEngine::Model::Board* board2 = new ChessEngine::Model::Board(*test.board1);
    ChessEngine::Controller::BoardController c_board2(*board2, test.player);

    // get board 2 pieces
    auto queen2 = c_board2.GetPieceSafe(test.queenPosition);
    auto horse2 = c_board2.GetPieceSafe(test.horsePosition);

    EXPECT_TRUE(&test.queen1 != &queen2);
    EXPECT_TRUE(&horse2 != &test.horse1);
};

#endif