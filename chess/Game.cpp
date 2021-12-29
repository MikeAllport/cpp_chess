#include "Game.h"

namespace Chess
{
    
    const Colour Chess::Game::CAN_MOVE_COLOUR = Colour(50, 166, 108, 255);

    Game::Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game):
        m_p1(player1), m_p2(player2), c_game(c_game), currentMouseTile(0, 0), currentMoves(nullptr)
    {
        OnEndOfTurn();
    }

    void Game::OnRender(sf::RenderWindow& window)
    {
        RenderBoard(window);
        if((*currentMoves).count(currentMouseTile))
        {
            RenderTileColour(window, currentMouseTile, CAN_MOVE_COLOUR);
        }
    }

    void Game::RenderTileColour(sf::RenderWindow& window, const Point& tilePoint, const Colour& colour)
    {
        sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tileShape.setPosition(sf::Vector2f(tilePoint.GetX() * (float) TILE_SIZE, tilePoint.GetY() * (float) TILE_SIZE));
        tileShape.setFillColor(colour);
        window.draw(tileShape);
    }

    void Game::OnEvent(const sf::Event& event)
    {
        switch(event.type)
        {
            case sf::Event::MouseMoved:
                SetMouseTilePosition(event);
                break;
            default:
                break;
        }
    }

    void Game::OnEndOfTurn()
    {
        if(currentMoves != 0)
        {
            delete currentMoves;
        }
        auto moves = c_game.GetActivePlayersMoves();
        currentMoves = new std::map<Point, VectorHelper<Move>>(c_game.GetActivePlayersMoves());
    }

    void Game::SetMouseTilePosition(const sf::Event& event)
    {
        auto tilePos = MouseToTile(event.mouseMove.x, event.mouseMove.y);
        if (currentMouseTile.GetX() != tilePos.GetX() ||
            currentMouseTile.GetY() != tilePos.GetY())
            currentMouseTile = tilePos;
    }

    void Game::RenderBoard(sf::RenderWindow& window)
    {
        auto image = Chess::Textures::Board;
        sf::Sprite sprite;
        sprite.setTexture(image);
        window.draw(sprite);
    }

    Point Game::MouseToTile(const int &x, const int &y)
    {
        return Point(x / TILE_SIZE, y / TILE_SIZE);
    }
}