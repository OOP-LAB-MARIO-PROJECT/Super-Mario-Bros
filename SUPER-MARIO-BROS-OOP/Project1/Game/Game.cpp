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
	textureManager->loadFromInterface("Assets/Textures/texture_interface.txt");

	sceneManager = &SceneManager::getInstance();
	
	sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));
	sceneManager->addScene(SceneManager::Scenes::Exit, new ExitScene(window));

	m_isRunning = true;
};

//void Game::run() {
//	if (!window->isOpen()) {
//		m_isRunning = false;
//		return;
//	}
//
//	float deltatime = m_clock.restart().asSeconds();
//	
//	sf::Event event;
//	while (window->pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window->close();
//	}
//	
//	// UPDATE HERE
//
//
//	// END UPDATE
// 
//
//
// 
//	// RENDER HERE
//
//	// END RENDER
//	sf::CircleShape shape(100.f);
//	shape.setFillColor(sf::Color::Green);
//	window->clear();
//	window->draw(shape);
//	window->display();
//};

void Game::run() {
	if (!window->isOpen()) {
		m_isRunning = false;
		return;
	}

	float deltatime = m_clock.restart().asSeconds();


	window->clear();
	sceneManager->update(deltatime);
	window->display();
};

void Game::exit() {
	window->close();
};

bool Game::isRunning() const {
	return m_isRunning;
};
