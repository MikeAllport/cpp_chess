#include "GameController.h"

namespace Chess::Controller
{
    GameController::GameController(const Model::Player& p1, const Model::Player& p2, MoveTikrintojas* c_moveCheck):
        m_game(p1, p2, c_moveCheck) {}

    void GameController::initialiseBoard(const Model::Player& p1, const Model::Player& p2)
    {
            auto bottomColour = p1.IsWhite()? Model::Enums::WHITE: Model::Enums::BLACK;
            auto topColour = p1.IsWhite()? Model::Enums::BLACK: Model::Enums::WHITE;
            // place pawns
            for(int i = 0; i < 8; ++i)
            {
                auto topPawn = new Model::Pawn(topColour, Model::Point(1, i));
                auto bottomPawn = new Model::Pawn(bottomColour, Model::Point(6, i));
                m_game.c_board.AddPiece({topPawn, bottomPawn});
            }

            // place doubles
            for(int i = 0; i < 2; ++i)
            {
                int topY = 0, bottomY = 7;

                int xPos = i*7;
                auto castleTop = new Model::Castle(topColour, Model::Point(xPos, topY));
                auto castleBottom = new Model::Castle(bottomColour, Model::Point(xPos, bottomY));

                xPos = i * 5 + 1;
                auto horseTop = new Model::Horse(topColour, Model::Point(xPos, topY));
                auto horseBottom = new Model::Horse(bottomColour, Model::Point(xPos, bottomY));

                xPos = i * 3 + 2;
                auto bishopTop = new Model::Bishop(topColour, Model::Point(xPos, topY));
                auto bishopBottom = new Model::Bishop(bottomColour, Model::Point(xPos, bottomY));

                m_game.c_board.AddPiece({castleBottom, castleTop, horseBottom, horseTop, bishopBottom, bishopTop});
            }

            // king queen
            auto queenTop = new Model::Queen(topColour, Model::Point(0, 3));
            auto queenBottom = new Model::Queen(bottomColour, Model::Point(7, 3));
            auto kingTop = new Model::King(topColour, Model::Point(0, 4));
            auto kingBottom = new Model::King(bottomColour, Model::Point(7, 4));

            m_game.c_board.AddPiece({queenTop, queenBottom, kingTop, kingBottom});
    }

    void GameController::TakeTurn(const Model::Move& move)
    {
        m_game.c_board.MakeMove(move);
        m_game.m_playersTurn = m_game.m_playersTurn == Model::Enums::WHITE? Model::Enums::BLACK: Model::Enums::WHITE;
    }

    bool GameController::IsGameOver()
    {
        return m_game.c_move.GetAllColoursMoves(m_game.m_playersTurn).empty();
    }

    const Model::Player GameController::GetWinner() const
    {
        return m_game.m_playersTurn == Model::Enums::WHITE? *m_game.m_whitePlayer: *m_game.m_blackPlayer;
    }
}