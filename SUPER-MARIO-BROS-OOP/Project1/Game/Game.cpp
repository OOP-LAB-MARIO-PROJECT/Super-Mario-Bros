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

	soundManager = &SoundManager::getInstance();
	soundManager->loadFromInterface("Assets/Sounds/sound_interface.txt");
	
	sceneManager = &SceneManager::getInstance();
	sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));
	sceneManager->addScene(SceneManager::Scenes::Exit, new ExitScene(window));
	sceneManager->addScene(SceneManager::Scenes::Game, new GameScene(window));
	sceneManager->navigateTo(SceneManager::Scenes::Game);

	m_isRunning = true;
};

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
