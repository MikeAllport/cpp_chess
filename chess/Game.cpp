#include "Game.h"

namespace Chess
{
    Game::Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game):
        m_p1(player1), m_p2(player2), c_game(c_game) {}

    void Game::OnRender(sf::RenderWindow& window)
    {
        RenderBoard(window);
    }

    void Game::RenderBoard(sf::RenderWindow& window)
    {
        auto image = Chess::Textures::Board;
        sf::Sprite sprite;
        sprite.setTexture(image);
        window.draw(sprite);
    }
}