#include "GameScene.h"
#include <fstream>
#include <exception>

GameScene::~GameScene() {
	delete player;
	delete gameMap;
	delete camera;

}

void GameScene::loadMapList() {
	// load map from txt file
	const std::string& mapList = "Assets/Map/map_interface.txt";
	std::ifstream fin(mapList);
	if (!fin.is_open()) {
		throw std::exception("Cannot open maplist\n");
	}

	std::string mapName, mapPath;
	while (fin >> mapName >> mapPath) {
		levelMap[mapName] = mapPath;
		std::cout << "Map loaded: " << mapName << ' ' << mapPath << '\n';
	}

	currentLevel = "map-1-1";
	GameConfig::getInstance().setCurrentLevel(currentLevel);
	GameConfig::getInstance().saveLevel();
	fin.close();
}


void GameScene::nextLevel(std::string level) {
	EntityManager::getInstance().clear();
	GameConfig::getInstance().saveLevel();
	GameConfig::getInstance().timeLeft = 300;
	GameConfig::getInstance().setCurrentLevel(level);
	GameConfig::getInstance().unlockedLevel[level] = { 0, 0 };
	GameConfig::getInstance().saveToFile();

	player->otherEntities.clear();
	player->obstacle.clear();
	player->nearPointerTiles.clear();
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
		nextLevel(GameConfig::getInstance().nextLevel);
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
	player->reset();
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
	myCommand.addCommand("shoot", new Shoot(player));

	myKeyExecute.addCommand(sf::Keyboard::W, myCommand.getCommand("jump"));
	myKeyExecute.addCommand(sf::Keyboard::A, myCommand.getCommand("moveLeft"));
	myKeyExecute.addCommand(sf::Keyboard::D, myCommand.getCommand("moveRight"));
	myKeyExecute.addCommand(sf::Keyboard::F, myCommand.getCommand("shoot"));
	EntityManager::getInstance().setRenderWindowForDebug(getWindow());
}


void GameScene::update(float deltatime) {

	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
	}

	if (deltatime > 0.03) {
		std::cout << "loading....\n";
		deltatime = 0.03;
	}

	myCommand.setDeltaTime(deltatime);
	myKeyExecute.handleInput();

	EntityManager::getInstance().renderAll(getWindow());
	EntityManager::getInstance().filter();
	
	player->update(deltatime);
	gameMap->update(deltatime, player->getPos(), player->getSize(), player->getVel(), player->currentMode);

	EntityManager::getInstance().setUpdatePivot(player->getPos());
	EntityManager::getInstance().updateAll(deltatime);
	
	gameMap->updateEnvironment();
	
	camera->followPlayer(player->getPos().x, player->getPos().y, player->getSize().x, player->getSize().y);
	camera->setCameraView(getWindow());

	
	gameMap->render(getWindow());
	player->render(getWindow());
	
	std::pair<sf::Vector2f, sf::Vector2f> renderSpace = camera->getRenderSpace();
	gameMap->setRenderSpace(renderSpace.first, renderSpace.second);
	camera->renderGameInfo(getWindow(), *FontManager::getInstance().getFont("Roboto").get(), GameConfig::getInstance());
	
	// check for level
	retrieveLevelStatus();
}