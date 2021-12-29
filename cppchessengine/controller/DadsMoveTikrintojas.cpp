#include "DadsMoveTikrintojas.h"

namespace ChessEngine::Controller
{
    bool DadsMoveTikrintojas::IsMoveValid(const Model::Move move, MoveController& c_move) const {
        return false;
    }
    bool DadsMoveTikrintojas::IsColourAttacking(const Model::Move move, MoveController& c_move) const {
        return false;
    }
}