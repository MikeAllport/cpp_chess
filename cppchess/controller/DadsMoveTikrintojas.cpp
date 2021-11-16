#include "DadsMoveTikrintojas.h"

namespace Chess::Controller
{
    bool DadsMoveTikrintojas::IsMoveValid(const Model::Move move, MoveController& c_move) const override {
        return false;
    }
    bool DadsMoveTikrintojas::IsColourAttacking(const Model::Move move, MoveController& c_move) const {
        return false;
    }
}