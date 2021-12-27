#ifndef CHESS_INTERFACES
#define CHESS_INTERFACES

#include <SFML/Graphics.hpp>

namespace Chess
{
    class IRenderer
    {
    public:
        virtual void OnRender(sf::RenderWindow& window) = 0;
    };

    class IEventHandler
    {
    public:
        virtual void OnEvent(const sf::Event& event) = 0;
    };
}

#endif