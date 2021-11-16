#include "DadsMoveTikrintojas.h"

namespace Chess::Controller
{
    bool DadsMoveTikrintojas::IsMoveValid(Model::Move move, MoveController& c_move) const
    {
        return false;
    }

    bool DadsMoveTikrintojas::IsColourUnderAttack(const bool isWhiteKing, MoveController& c_move) const
    {
        return false;
    }
}