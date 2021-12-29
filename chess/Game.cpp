#include "Game.h"

namespace Chess
{
    
    const ColourVec Chess::Game::PIECE_MOVE_TO_COLOUR = ColourVec(50, 166, 108, 175);
    const ColourVec Chess::Game::CAN_MOVE_COLOUR = ColourVec(127, 67, 196, 175);
    const ColourVec Chess::Game::PIECE_MOVE_TO_ATTACK_COLOUR = ColourVec(201, 36, 36, 175);
    
    Game::Game(ChessEngine::Model::Player& player1, ChessEngine::Model::Player& player2, ChessEngine::Controller::GameController& c_game):
        m_p1(player1), m_p2(player2), c_game(c_game), currentMouseTile(0, 0), currentMoves(nullptr), movingPiece(nullptr)
    {
        OnEndOfTurn();
    }

    void Game::OnRender(sf::RenderWindow& window)
    {
        RenderBoard(window);
        // paint can pick up piece under mouse
        if((*currentMoves).count(currentMouseTile) && movingPiece == nullptr)
        {
            RenderTileColour(window, currentMouseTile, CAN_MOVE_COLOUR);
        }
        Point attackingPiecePosition(-1, -1);
        // paint all moves a piece can make
        if(movingPiece != nullptr)
        {
            for(auto move: movingPiecesMoves.v)
            {
                auto colour = move.IsAttack()? PIECE_MOVE_TO_ATTACK_COLOUR: PIECE_MOVE_TO_COLOUR;
                RenderTileColour(window, move.ToPosition(), colour);
                // paint moving piece under mouse if a move
                if (currentMouseTile == move.ToPosition())
                {
                    RenderPiece(window, movingPiece, move.ToPosition());
                    attackingPiecePosition = move.ToPosition();
                }
            }
            RenderTileColour(window, movingPiece->GetPosition(), CAN_MOVE_COLOUR);
            if (currentMouseTile == movingPiece->GetPosition())
            {
                RenderPiece(window, movingPiece, currentMouseTile);
            }
        }
        // paint pieces
        for(auto piece: c_game.c_board.ActivePieces().v)
        {
            if(piece != movingPiece && !(piece->GetPosition() == attackingPiecePosition))
            {
                RenderPiece(window, piece, piece->GetPosition());
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
            case sf::Event::MouseButtonReleased:
                OnMouseClick(event);
                break;
            default:
                break;
        }
    }

    void Game::OnMouseClick(const sf::Event& event)
    {
        if(!event.mouseButton.button == sf::Mouse::Left)
        {
            return;
        }

        Point tilePosition = MouseToTile(event.mouseButton.x, event.mouseButton.y);

        // handle picking piece up to make a move
        if(movingPiece == nullptr)
        {
            if((*currentMoves).count(tilePosition))
            {
                movingPiece = c_game.c_board.GetPieceSafe(tilePosition);
                movingPiecesMoves = (*currentMoves)[tilePosition];
            }
            return;
        }

        // handle making a move
        auto move = movingPiecesMoves.FirstOrNull([&tilePosition](Move move) { return move.ToPosition() == tilePosition; });
        if(move)
        {
            movingPiece = nullptr;
            c_game.TakeTurn(move.value());
            OnEndOfTurn();
            return;
        }

        if(tilePosition == movingPiece->GetPosition())
        {
            movingPiece = nullptr;
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

    void Game::RenderPiece(sf::RenderWindow& window, const Piece* piece, const Point& position)
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