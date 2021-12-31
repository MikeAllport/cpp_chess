#ifndef CHESS_BOAD_EVAL
#define CHESS_BOARD_EVAL

#include "../cppchessengine/model/AllPiecesInclude.h"
#include "../cppchessengine/model/Enums.h"

using namespace ChessEngine::Model::Enums;
using Piece = ChessEngine::Model::Piece;

namespace Chess
{
    class BoardEvaluator
    {
    public:
        static int GetPiecePositionalScore(const Colour& p1Colour, const MoveCheckType& gameType, const Piece* piece)
        {
            bool isWhite = 
                p1Colour == WHITE && piece->IsWhite() || 
                p1Colour == BLACK && !piece->IsWhite()? 
                true: false;

            int posX = piece->GetPosition().GetX();
            int posY = piece->GetPosition().GetY();
            int points;
            switch(piece->GetType())
            {
            case PAWN:
                points = isWhite? P1PAWN[posY][posX]: P2PAWN[posY][posX];
                break;
            case CASTLE:
                points = isWhite? P1CASTLE[posY][posX]: P2CASTLE[posY][posX];
                break;
            case HORSE:
                points = isWhite? P1HORSE[posY][posX]: P2HORSE[posY][posX];
                break;
            case BISHOP:
                points = isWhite? P1BISH[posY][posX]: P2BISHOP[posY][posX];
                break;
            case QUEEN:
                points = isWhite? P1QUEEN[posY][posX]: P2QUEEN[posY][posX];
                break;
            default:
                points = isWhite? P1KING[posY][posX]: P2KING[posY][posX];
                break;
            }
            return gameType == DADS? -points: points;
        }
    private:
        static constexpr int P1PAWN[8][8] =
            {
                {100,  100,  100,  100,  100,  100,  100,  100},
                {75, 75, 75, 75, 75, 75, 75, 75},
                {25, 25, 29, 29, 29, 29, 25, 25},
                {5,  5, 10, 25, 25, 10,  5,  5},
                {0,  0,  0, 20, 20,  0,  0,  0},
                {5, -5,-10,  0,  0,-10, -5,  5},
                {5, 10, 10,-20,-20, 10, 10,  5},
                {0,  0,  0,  0,  0,  0,  0,  0}
            };

        static constexpr int P1HORSE[8][8] =
            {
                    {-50,-40,-30,-30,-30,-30,-40,-50},
                    {-40,-20,  0,  0,  0,  0,-20,-40},
                    {-30,  0, 10, 15, 15, 10,  0,-30},
                    {-30,  5, 15, 20, 20, 15,  5,-30},
                    {-30,  0, 15, 20, 20, 15,  0,-30},
                    {-30,  5, 10, 15, 15, 10,  5,-30},
                    {-40,-20,  0,  5,  5,  0,-20,-40},
                    {-50,-40,-30,-30,-30,-30,-40,-50}
            };

        static constexpr int P1BISH[8][8] =
            {
                    {-20,-10,-10,-10,-10,-10,-10,-20},
                    {-10,  0,  0,  0,  0,  0,  0,-10},
                    {-10,  0,  5, 10, 10,  5,  0,-10},
                    {-10,  5,  5, 10, 10,  5,  5,-10},
                    {-10,  0, 10, 10, 10, 10,  0,-10},
                    {-10, 10, 10, 10, 10, 10, 10,-10},
                    {-10,  5,  0,  0,  0,  0,  5,-10},
                    {-20,-10,-10,-10,-10,-10,-10,-20}
            };


        static constexpr int P1CASTLE[8][8] =
            {
                    {0,  0,  0,  0,  0,  0,  0,  0},
                    {5, 20, 20, 20, 20, 20, 20,  5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {-5,  0,  0,  0,  0,  0,  0, -5},
                    {0,  0,  0,  5,  5,  0,  0,  0}
            };

        static constexpr int P1QUEEN[8][8] =
            {
                    {-20,-10,-10, -5, -5,-10,-10,-20},
                    {-10,  0,  0,  0,  0,  0,  0,-10},
                    {-10,  0,  5,  5,  5,  5,  0,-10},
                    {-5,  0,  5,  5,  5,  5,  0, -5},
                    { 0,  0,  5,  5,  5,  5,  0, -5},
                    { -10,  5,  5,  5,  5,  5,  0,-10},
                    { -10,  0,  5,  0,  0,  0,  0,-10},
                    { -20,-10,-10, -5, -5,-10,-10,-20}
            };

        static constexpr int P1KING[8][8] =
            {
                    {-30,-40,-40,-50,-50,-40,-40,-30},
                    {-30,-40,-40,-50,-50,-40,-40,-30},
                    {-30,-40,-40,-50,-50,-40,-40,-30},
                    {-30,-40,-40,-50,-50,-40,-40,-30},
                    {-20,-30,-30,-40,-40,-30,-30,-20},
                    {-10,-20,-20,-20,-20,-20,-20,-10},
                    {20, 20,  0,  0,  0,  0, 20, 20},
                    {20, 30, 10,  0,  0, 10, 30, 20}
            };

        static constexpr int P2PAWN[8][8] =
            {
                {0,  0,  0,  0,  0,  0,  0,  0},
                {5, 10, 10,-20,-20, 10, 10,  5},
                {5, -5,-10,  0,  0,-10, -5,  5},
                {0,  0,  0, 20, 20,  0,  0,  0},
                {5,  5, 10, 25, 25, 10,  5,  5},
                {25, 25, 29, 29, 29, 29, 25, 25},
                {75, 75, 75, 75, 75, 75, 75, 75},
                {100,  100,  100,  100,  100,  100,  100,  100},
            };


        static constexpr int P2HORSE[8][8] =
            {
                {-50,-40,-30,-30,-30,-30,-40,-50},
                {-40,-20,  0,  5,  5,  0,-20,-40},
                {-30,  5, 10, 15, 15, 10,  5,-30},
                {-30,  0, 15, 20, 20, 15,  0,-30},
                {-30,  5, 15, 20, 20, 15,  5,-30},
                {-30,  0, 10, 15, 15, 10,  0,-30},
                {-40,-20,  0,  0,  0,  0,-20,-40},
                {-50,-40,-30,-30,-30,-30,-40,-50}
            };

        static constexpr int P2BISHOP[8][8] =
            {
                {-20,-10,-10,-10,-10,-10,-10,-20},
                {-10,  5,  0,  0,  0,  0,  5,-10},
                {-10, 10, 10, 10, 10, 10, 10,-10},
                {-10,  0, 10, 10, 10, 10,  0,-10},
                {-10,  5,  5, 10, 10,  5,  5,-10},
                {-10,  0,  5, 10, 10,  5,  0,-10},
                {-10,  0,  0,  0,  0,  0,  0,-10},
                {-20,-10,-10,-10,-10,-10,-10,-20}
            };


        static constexpr int P2CASTLE[8][8] =
            {
                {0,  0,  0,  5,  5,  20,  0,  0},
                { -5,  0,  0,  0,  0,  0,  0, -5},
                { -5,  0,  0,  0,  0,  0,  0, -5},
                { -5,  0,  0,  0,  0,  0,  0, -5},
                { -5,  0,  0,  0,  0,  0,  0, -5},
                {-5,  0,  0,  0,  0,  0,  0, -5},
                { 5, 20, 20, 20, 20, 20, 20,  5},
                {0,  0,  0,  0,  0,  0,  0,  0}
            };


        static constexpr int P2QUEEN[8][8] =
            {
                {-20,-10,-10, -5, -5,-10,-10,-20},
                {-10,  0,  5,  0,  0,  0,  0,-10},
                {-10,  5,  5,  5,  5,  5,  0,-10},
                { 0,  0,  5,  5,  5,  5,  0, -5},
                {0,  0,  5,  5,  5,  5,  0, -5},
                {-10,  0,  5,  5,  5,  5,  0,-10},
                {-10,  0,  0,  0,  0,  0,  0,-10},
                {-20,-10,-10, -5, -5,-10,-10,-20},
            };

        static constexpr int P2KING[8][8] =
            {
                {20, 30, 10,  0,  0, 10, 60, 20},
                {20, 20,  0,  0,  0,  0, 20, 20},
                {-10,-20,-20,-20,-20,-20,-20,-10},
                {-20,-30,-30,-40,-40,-30,-30,-20},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
                {-30,-40,-40,-50,-50,-40,-40,-30},
            };
    };
}

#endif