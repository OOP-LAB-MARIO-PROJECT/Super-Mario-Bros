#include "Game.h"

Game::~Game() {
	delete window;
};

void Game::start() {
	// Basic window setup -> will change after
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Mario");
	window->setFramerateLimit(60);
	m_clock.restart();
	
	
	textureManager = &TextureManager::getInstance();
	textureManager->loadNewTexture("Assets/Textures/Texture_Pack/mario.tsx", "Assets/Textures/Texture_Pack/mario.png");

	sceneManager = &SceneManager::getInstance();

	sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));

	m_isRunning = true;
};

void Game::run() {
	if (!window->isOpen()) {
		m_isRunning = false;
		return;
	}

	float deltatime = m_clock.restart().asSeconds();
	
	window->clear(sf::Color::Black);

	sf::Event event;
	
	// UPDATE HERE

	sceneManager->update(deltatime);

	// END UPDATE
 
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();
	}

	// RENDER HERE

	// END RENDER
	window->display();
};

void Game::exit() {
	window->close();
};

bool Game::isRunning() const {
	return m_isRunning;
};
