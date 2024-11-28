#include "GameScene.h"
#include <fstream>
#include <exception>

GameScene::~GameScene() {
	delete player;
	delete gameMap;
	delete camera;

}

void GameScene::loadMapList() {
	const std::string& mapList = "Assets/Map/map_interface.txt";

	std::ifstream fin(mapList);
	if (!fin.is_open()) {
		throw std::exception("Cannot open maplist\n");
	}

	std::string mapName, mapPath;
	while (fin >> mapName >> mapPath) {
		levelMap[mapName] = mapPath;
	}

	currentLevel = "map-1-1";
	GameConfig::getInstance().setCurrentLevel(currentLevel);

	fin.close();
}


void GameScene::nextLevel(std::string level) {
	EntityManager::getInstance().clear();

	GameConfig::getInstance().timeLeft = 300;
	GameConfig::getInstance().setCurrentLevel(level);
	std::cout << "move to " << level << '\n';
	currentLevel = level;
	delete gameMap;
	gameMap = new Map();
	gameMap->loadMap(levelMap[currentLevel], player);
}

void GameScene::retrieveLevelStatus() {
	LEVEL_STATUS& status = GameConfig::getInstance().levelStatus;
	if (status == PLAYING) return;

	if (status == RESTART) {
		status = PLAYING;
		restartLevel();
		return;
	}

	if (status = NEXT_LEVEL) {
		status = PLAYING;
		nextLevel(GameConfig::getInstance().currentLevel);
	}
}


void GameScene::restartLevel() {
	EntityManager::getInstance().clear();

	GameConfig::getInstance().marioState = SMALL;
	GameConfig::getInstance().coins = 0;
	GameConfig::getInstance().score = 0;
	GameConfig::getInstance().timeLeft = 300;

	delete gameMap;
	gameMap = new Map();
	gameMap->loadMap(levelMap[currentLevel], player);
}

GameScene::GameScene(sf::RenderWindow* window) : Scene(window) {
	// INITIALIZE 
	
	loadMapList();

	player = new Player(sf::Vector2f(50, 50), sf::Vector2f(14, 14));
	restartLevel();

	std::cout << gameMap->getPlayerPos().x << ' ' << gameMap->getPlayerPos().y << "\n";
	camera = new Camera(window, gameMap->getPlayerPos());

	myCommand.addCommand("jump", new Jump(player));
	myCommand.addCommand("moveLeft", new MoveLeft(player));
	myCommand.addCommand("moveRight", new MoveRight(player));

	myKeyExecute.addCommand(sf::Keyboard::W, myCommand.getCommand("jump"));
	myKeyExecute.addCommand(sf::Keyboard::A, myCommand.getCommand("moveLeft"));
	myKeyExecute.addCommand(sf::Keyboard::D, myCommand.getCommand("moveRight"));
}


void GameScene::update(float deltatime) {
	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
	}

	myCommand.setDeltaTime(deltatime);
	myKeyExecute.handleInput();

	gameMap->update(deltatime, player->getPos(), player->getSize(), player->getVel(), player->currentMode);
	player->update(deltatime);

	camera->followPlayer(player->getPos().x, player->getPos().y, player->getSize().x, player->getSize().y);
	camera->setCameraView(getWindow());


	player->render(getWindow());
	gameMap->render(getWindow());
	if (FontManager::getInstance().getFont("Roboto").get() == nullptr)
		std::cout << "cannot getfont in game\n";
	camera->renderGameInfo(getWindow(), *FontManager::getInstance().getFont("Roboto").get(), GameConfig::getInstance());

	EntityManager::getInstance().filter();


	// check for level
	retrieveLevelStatus();
}