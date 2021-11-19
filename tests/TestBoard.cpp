#ifndef CHESS_TEST_StandardTikrintojas_CONTROLLER
#define CHESS_TEST_StandardTikrintojas_CONTROLLER

#include <gtest/gtest.h>
#include "../cppchess/controller/MoveController.h"
#include "../cppchess/controller/BoardController.h"
#include "../cppchess/model/Board.h"
#include "../cppchess/model/AllPiecesInclude.h"
#include "../cppchess/model/Piece.h"
#include "../cppchess/model/Pawn.h"
#include "../cppchess/model/Point.h"

class TestBoard
{
public:
    TestBoard():
        board1(new Chess::Model::Board()),
        player(Chess::Model::Enums::P1, Chess::Model::Enums::WHITE),
        c_board1(*board1, player),
        queenPosition(0,0),
        horsePosition(7,7),
        queen1(new Chess::Model::Queen(Chess::Model::Enums::WHITE, queenPosition)),
        horse1(new Chess::Model::Horse(Chess::Model::Enums::WHITE, horsePosition)) 
        {
            c_board1.AddPiece({queen1, horse1});
        }
    ~TestBoard() { delete board1; }
    Chess::Model::Board* board1;
    Chess::Model::Player player;
    Chess::Controller::BoardController c_board1;
    Chess::Model::Point queenPosition;
    Chess::Model::Point horsePosition;
    Chess::Model::Piece* queen1;
    Chess::Model::Piece* horse1;
};

TEST(Board, CopyingBoardWorks)
{
    TestBoard test;
    // init board 2
    Chess::Model::Board* board2 = new Chess::Model::Board(*test.board1);
    Chess::Controller::BoardController c_board2(*board2, test.player);

    // get board 2 pieces
    auto queen2 = c_board2.GetPieceSafe(test.queenPosition);
    auto horse2 = c_board2.GetPieceSafe(test.horsePosition);

    EXPECT_TRUE(&test.queen1 != &queen2);
    EXPECT_TRUE(&horse2 != &test.horse1);
};

#endif