#ifndef CHESS_GAME
#define CHESS_GAME


#include <iostream>
#include <SFML/Graphics.hpp>
#include "../cppchessengine/controller/GameController.h"
#include "../cppchessengine/model/Enums.h"
#include "Textures.h"
#include "Interfaces.h"

namespace Chess
{
    class Game: public IRenderer
    {
    public:
        Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game);
        void OnRender(sf::RenderWindow& window) override;
        static const int WINDOW_SIZE = 800, TILE_SIZE = 100;
    private:
        void RenderBoard(sf::RenderWindow& window);
        ChessEngine::Controller::GameController& c_game;
        ChessEngine::Model::Player &m_p1, &m_p2;
    };
}

#endif