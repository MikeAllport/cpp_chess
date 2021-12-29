#include "Game.h"

namespace Chess
{
    
    const ColourVec Chess::Game::CAN_MOVE_COLOUR = ColourVec(50, 166, 108, 200);

    Game::Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game):
        m_p1(player1), m_p2(player2), c_game(c_game), currentMouseTile(0, 0), currentMoves(nullptr), movingPiece(nullptr)
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
        for(auto piece: c_game.c_board.ActivePieces().v)
        {
            if(piece != movingPiece)
            {
                RenderPiece(window, piece);
            }
        }
    }

    void Game::RenderTileColour(sf::RenderWindow& window, const Point& tilePoint, const ColourVec& colour)
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

    void Game::RenderPiece(sf::RenderWindow& window, const Piece* piece)
    {
        Texture text;
        bool isWhite = piece->IsWhite();
        switch(piece->GetType())
        {
            case PAWN:
                text = isWhite? Textures::WhitePawn: Textures::BlackPawn;
                break;
            case CASTLE:
                text = isWhite? Textures::WhiteCastle: Textures::BlackCastle;
                break;
            case HORSE:
                text = isWhite? Textures::WhiteHorse: Textures::BlackHorse;
                break;
            case BISHOP:
                text = isWhite? Textures::WhiteBishop: Textures::BlackBishop;
                break;
            case QUEEN:
                text = isWhite? Textures::WhiteQueen: Textures::BlackQueen;
                break;
            default:
                text = isWhite? Textures::WhiteKing: Textures::BlackKing;
                break;
        }
        sf::RectangleShape tileShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        auto position = piece->GetPosition();
        tileShape.setPosition(sf::Vector2f(position.GetX() * (float) TILE_SIZE, position.GetY() * (float) TILE_SIZE));
        tileShape.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tileShape.setTexture(&text);
        window.draw(tileShape);
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