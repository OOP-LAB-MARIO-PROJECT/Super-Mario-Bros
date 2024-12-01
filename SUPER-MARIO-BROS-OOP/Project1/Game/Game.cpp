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

	sceneManager = &SceneManager::getInstance();

	sceneManager->addScene(SceneManager::Scenes::Login, new LoginScene(window));
	sceneManager->addScene(SceneManager::Scenes::Register, new RegisterScene(window));
	sceneManager->addScene(SceneManager::Scenes::Home, new HomeScene(window));
	sceneManager->addScene(SceneManager::Scenes::Exit, new ExitScene(window));
	sceneManager->addScene(SceneManager::Scenes::Game, new GameScene(window));
	sceneManager->addScene(SceneManager::Scenes::Setting, new SettingScene(window));

	sceneManager->navigateTo(SceneManager::Scenes::Setting);
	

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
	//::cout << "FPS: " << 1 / deltatime << '\n';

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
