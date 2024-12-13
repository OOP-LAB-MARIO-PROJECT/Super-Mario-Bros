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
	if (status == PLAYING || status == PAUSE) return;

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
	myCommand.addCommand("left", new MoveLeft(player));
	myCommand.addCommand("right", new MoveRight(player));
	myCommand.addCommand("shoot", new Shoot(player));
	myCommand.addCommand("pause", new Pause());
	//myCommand.addCommand("dodge", new Shoot(player));

	myKeyExecute.addCommand(GameConfig::getInstance().getControl("jump"), myCommand.getCommand("jump"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("left"), myCommand.getCommand("left"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("right"), myCommand.getCommand("right"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("shoot"), myCommand.getCommand("shoot"));
	myKeyExecute.addCommand(sf::Keyboard::Escape, myCommand.getCommand("pause"));

	EntityManager::getInstance().setRenderWindowForDebug(getWindow());
}

void GameScene::updateControlKey() {
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("jump"), myCommand.getCommand("jump"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("left"), myCommand.getCommand("left"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("right"), myCommand.getCommand("right"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("shoot"), myCommand.getCommand("shoot"));
}

void GameScene::update(float deltatime) {
	

	if (GameConfig::getInstance().hasKeyChanges) {
		GameConfig::getInstance().hasKeyChanges = false;
		updateControlKey();
	}

	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}

		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape) {
				myCommand.executeCommand("pause");
			}
	}


	if (deltatime > 0.3) deltatime = 0.3;
	myCommand.setDeltaTime(deltatime);
	myKeyExecute.handleInput();


	//if (GameConfig::getInstance().levelStatus == PAUSE) return;

	EntityManager::getInstance().renderAll(getWindow());
	EntityManager::getInstance().filter();
	
	if (GameConfig::getInstance().levelStatus != PAUSE) {

		player->update(deltatime);
		gameMap->update(deltatime, player->getPos(), player->getSize(), player->getVel(), player->currentMode);

		EntityManager::getInstance().updateAll(deltatime);
		EntityManager::getInstance().setUpdatePivot(player->getPos());
	
		gameMap->updateEnvironment();

		camera->followPlayer(player->getPos().x, player->getPos().y, player->getSize().x, player->getSize().y);
	
	}
	

	camera->setCameraView(getWindow());
	
	gameMap->render(getWindow());
	player->render(getWindow());
	
	std::pair<sf::Vector2f, sf::Vector2f> renderSpace = camera->getRenderSpace();
	gameMap->setRenderSpace(renderSpace.first, renderSpace.second);
	camera->renderGameInfo(getWindow(), *FontManager::getInstance().getFont("Roboto").get(), GameConfig::getInstance());
	
	// check for level
	retrieveLevelStatus();
}