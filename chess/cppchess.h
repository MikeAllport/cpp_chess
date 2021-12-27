// cppchessengine.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../cppchessengine/model/Piece.h"
#include "../cppchessengine/model/Pawn.h"
#include "../cppchessengine/model/King.h"
#include "../cppchessengine/model/Queen.h"
#include "../cppchessengine/model/Bishop.h"
#include "../cppchessengine/model/Horse.h"
#include "../cppchessengine/model/Castle.h"
#include "../cppchessengine/model/Board.h"
#include "../cppchessengine/model/Player.h"
#include "../cppchessengine/utils/VectorHelper.h"
#include "../cppchessengine/model/Move.h"
#include "../cppchessengine/controller/MoveController.h"
#include "../cppchessengine/controller/BoardController.h"
#include "../cppchessengine/controller/MoveTikrintojas.h"


namespace Chess
{
    class Textures
    {
    public:
        static sf::Texture InitTexture(std::string fileuri) {
            sf::Texture result;
            if (!result.loadFromFile(fileuri))
            {
                throw "Error loading " + fileuri;
            }
            result.setSmooth(true);
            return result;
        }
        static sf::Texture Board;
    };
}

// TODO: Reference additional headers your program requires here.
