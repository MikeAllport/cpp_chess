#ifndef CHESS_GAME
#define CHESS_GAME


#include <iostream>
#include <SFML/Graphics.hpp>
#include "../cppchessengine/model/Point.h"
#include "../cppchessengine/model/Move.h"
#include "../cppchessengine/model/Piece.h"
#include "../cppchessengine/controller/GameController.h"
#include "../cppchessengine/model/Enums.h"
#include "Textures.h"
#include "Interfaces.h"

using Point = ChessEngine::Model::Point;
using Move = ChessEngine::Model::Move;
using Piece = ChessEngine::Model::Piece;
using Colour = sf::Color;

namespace Chess
{
    class Game: public IRenderer, public IEventHandler
    {
    public:
        Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game);
        void OnRender(sf::RenderWindow& window) override;
        void OnEvent(const sf::Event& event) override;
        static const int WINDOW_SIZE = 800, TILE_SIZE = 100;
        static const Colour CAN_MOVE_COLOUR;
    private:
        void OnEndOfTurn();
        void RenderBoard(sf::RenderWindow& window);
        void RenderPieceUnderMouseCanMove(sf::RenderWindow& window);
        void RenderTileColour(sf::RenderWindow& window, const Point &tilePos, const Colour& colour);
        void SetMouseTilePosition(const sf::Event& event);
        Point MouseToTile(const int &x, const int &y);

        std::map<Point, VectorHelper<Move>>* currentMoves;
        Point currentMouseTile;
        ChessEngine::Controller::GameController& c_game;
        ChessEngine::Model::Player &m_p1, &m_p2;
    };
}

#endif