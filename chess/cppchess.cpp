// cppchessengine.cpp : Defines the entry point for the application.
//

#include "cppchess.h"
#include "../cppchessengine/model/Player.h"
using Vec2D = sf::Vector2f;
using Window = sf::RenderWindow;

using namespace std;

void HandleEvents(sf::RenderWindow& window, Chess::Game& m_game)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
		{
			window.close();
		}
		m_game.OnEvent(event);
	}
}

float FRAMERATE = 1/60.f;
int main()
{
	// setp game for now
	ChessEngine::Model::Player m_p1(ChessEngine::Model::Enums::P1, ChessEngine::Model::Enums::WHITE);
	ChessEngine::Model::Player m_p2(ChessEngine::Model::Enums::P2, ChessEngine::Model::Enums::BLACK);
	ChessEngine::Model::Game m_chessEngineGame(m_p1, m_p2);
	ChessEngine::Controller::GameController c_game(m_chessEngineGame, ChessEngine::Model::Enums::MoveCheckType::DADS);
	c_game.InitialiseGame();
	Chess::Game m_game(m_p1, m_p2, c_game);
	sf::RenderWindow window(sf::VideoMode(Chess::Game::WINDOW_SIZE, Chess::Game::WINDOW_SIZE), "SFML Works!");

	sf::Clock clock;
	sf::Time timePassed = sf::Time::Zero;
	while(window.isOpen())
	{
		HandleEvents(window, m_game);
		timePassed += clock.restart();
		while(timePassed.asSeconds() < FRAMERATE)
		{
			sf::sleep(sf::seconds(1/6000.f));
			timePassed += clock.restart();
		}
		timePassed = sf::Time::Zero;
		window.clear();
		m_game.OnRender(window);
		window.display();
	}
	cout << "Hello CMake." << endl;
	return 0;
}

