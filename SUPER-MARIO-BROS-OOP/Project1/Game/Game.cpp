#include "Game.h"

Game::~Game() {
	delete window;
};

void Game::start() {
	// Basic window setup -> will change after
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int screenWidth = desktop.width / 8;

	window = new sf::RenderWindow(sf::VideoMode(screenWidth * 5, screenWidth * 3), "Mario");
	window->setFramerateLimit(60);
	m_clock.restart();
	
	
	textureManager = &TextureManager::getInstance();
	textureManager->loadFromInterface("Assets/Textures/texture_interface.txt");

	soundManager = &SoundManager::getInstance();
	soundManager->loadFromInterface("Assets/Sounds/sound_interface.txt");

	fontManager = &FontManager::getInstance();
	fontManager->loadFromInterface("Assets/Fonts/font_interface.txt");

	gameConfig = &GameConfig::getInstance();

	gameConfig->addControl("jump", sf::Keyboard::W);
	gameConfig->addControl("left", sf::Keyboard::A);
	gameConfig->addControl("right", sf::Keyboard::D);
	gameConfig->addControl("dodge", sf::Keyboard::S);
	gameConfig->addControl("shoot", sf::Keyboard::F);
	
	sceneManager = &SceneManager::getInstance();

	sceneManager->addScene(SceneManager::Scenes::Login, new LoginScene(window));
	sceneManager->addScene(SceneManager::Scenes::Register, new RegisterScene(window));
	sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));
	sceneManager->addScene(SceneManager::Scenes::Exit, new ExitScene(window));
	sceneManager->addScene(SceneManager::Scenes::Map, new MapScene(window));
	sceneManager->addScene(SceneManager::Scenes::Setting, new SettingScene(window));
	sceneManager->addScene(SceneManager::Scenes::KeyBinding, new KeyBindingScene(window));
	
	sceneManager->addScene(SceneManager::Scenes::Game, new GameScene(window));

	sceneManager->navigateTo(SceneManager::Scenes::Login);
	

	m_isRunning = true;
};

void Game::run() {
	if (!window->isOpen()) {
		m_isRunning = false;
		return;
	}

	float deltatime = m_clock.restart().asSeconds();
	int FPS = 1 / deltatime;

	window->clear(sf::Color::abell);
	sceneManager->update(deltatime);
	window->display();
};

void Game::exit() {
	window->close();
};

bool Game::isRunning() const {
	return m_isRunning;
};
