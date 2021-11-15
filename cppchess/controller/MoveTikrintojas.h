#ifndef CHESS_CONTROLLER_MOVETIKRINTOJAS
#define CHESS_CONTROLLER_MOVETIKRINTOJAS

/*
    First file to be commented, given naming. Partner and I could not decide between
    move evaluator or move validator, so gave it a lithuanian name for checker.

    This pure abstract class defines a method to validate a move. The concrete class's
    will have to implement this to return true/false if a move is valid
*/

namespace Chess::Controller
{
    class MoveTikrintojas
    {
    public:
        virtual bool IsMoveValid() const = 0;
    };
}
#endif