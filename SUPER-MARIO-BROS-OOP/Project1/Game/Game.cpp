#include "Game.h"

Game::~Game() {
	delete window;
};

void Game::start() {
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mario");
	window->setFramerateLimit(60);
	m_clock.restart();


	m_isRunning = true;
};

void Game::run() {
	if (!window->isOpen()) {
		m_isRunning = false;
		return;
	}

	float deltatime = m_clock.restart().asSeconds();
	
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}
	
	// UPDATE HERE


	// END UPDATE
 


 
	// RENDER HERE

	// END RENDER
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	window->clear();
	window->draw(shape);
	window->display();
};

void Game::exit() {
	window->close();
};

bool Game::isRunning() const {
	return m_isRunning;
};
