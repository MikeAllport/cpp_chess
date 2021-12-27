#ifndef CHESS_TEXTURES
#define CHESS_TEXTURES

#include <SFML/Graphics.hpp>
#include <iostream>
using Texture = sf::Texture;
namespace Chess
{
    class Textures
    {
    public:
        static Texture InitTexture(std::string fileuri) {
            Texture result;
            if (!result.loadFromFile(fileuri))
            {
                throw "Error loading " + fileuri;
            }
            std::cout << "Loaded " << fileuri << std::endl;
            result.setSmooth(true);
            return result;
        }
        static Texture Board, 
        BlackKing, BlackQueen, BlackBishop, BlackHorse, BlackCastle, BlackPawn,
        WhiteKing, WhiteQueen, WhiteBishop, WhiteHorse, WhiteCastle, WhitePawn;
    };
}

#endif