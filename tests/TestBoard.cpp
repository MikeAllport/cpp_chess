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

TEST(Board, CopyingBoardWorks)
{
    // init board 1
    Chess::Model::Board* board1 = new Chess::Model::Board();
    Chess::Model::Player player(Chess::Model::Enums::P1, Chess::Model::Enums::WHITE);
    Chess::Controller::BoardController c_board1(*board1, player);
    auto queenPosition = Chess::Model::Point(0,0);
    auto horsePosition = Chess::Model::Point(7, 7);
    Chess::Model::Piece* queen1 = new Chess::Model::Queen(Chess::Model::Enums::WHITE, queenPosition);
    Chess::Model::Piece* horse1 = new Chess::Model::Horse(Chess::Model::Enums::WHITE, horsePosition);
    c_board1.AddPiece({queen1, horse1});

    // init board 2
    Chess::Model::Board* board2 = new Chess::Model::Board(*board1);
    Chess::Controller::BoardController c_board2(*board2, player);

    // get board 2 pieces
    auto queen2 = c_board2.GetPieceSafe(queenPosition);
    auto horse2 = c_board2.GetPieceSafe(horsePosition);

    EXPECT_TRUE(&queen1 != &queen2);
    EXPECT_TRUE(&horse2 != &horse1);
}


#endif