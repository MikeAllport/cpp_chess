// cppchessengine.cpp : Defines the entry point for the application.
//

#include "cppchess.h"

using Vec2D = sf::Vector2f;
using Window = sf::RenderWindow;

using namespace std;

sf::Texture Chess::Textures::Board = Chess::Textures::InitTexture("res/board.png");

void drawBoard(Window& window)
{
	auto image = Chess::Textures::Board;
	sf::Sprite sprite;
	sprite.setTexture(image);
	window.draw(sprite);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800,800), "SFML Works!");
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		drawBoard(window);
		window.display();
	}
	cout << "Hello CMake." << endl;
	VectorHelper<int> list;
	list.v = { 1, 2, 3, 4, 5 };
	auto newList = list.Filter([](int a) { return a == 1 || a == 2; });
	for (int a : newList.v)
	{
		std::cout << a << endl;;
	}
	return 0;
}
