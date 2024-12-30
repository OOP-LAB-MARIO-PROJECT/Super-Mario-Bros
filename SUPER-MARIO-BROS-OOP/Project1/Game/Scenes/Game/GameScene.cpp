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
	levelMap = GameConfig::getInstance().mapList;
	currentLevel = GameConfig::getInstance().chosenMap;
	std::cout << "loadmaplist: " << currentLevel << '\n';
	GameConfig::getInstance().setCurrentLevel(currentLevel);
	GameConfig::getInstance().saveLevel();
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

	camera = new Camera(window, player->getPos());

	myCommand.addCommand("jump", new Jump(player));
	myCommand.addCommand("left", new MoveLeft(player));
	myCommand.addCommand("right", new MoveRight(player));
	myCommand.addCommand("dodge", new MoveDown(player));
	myCommand.addCommand("shoot", new Shoot(player));
	myCommand.addCommand("pause", new Pause());

	myKeyExecute.addCommand(GameConfig::getInstance().getControl("jump"), myCommand.getCommand("jump"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("left"), myCommand.getCommand("left"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("right"), myCommand.getCommand("right"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("shoot"), myCommand.getCommand("shoot"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("dodge"), myCommand.getCommand("dodge"));
	myKeyExecute.addCommand(sf::Keyboard::Escape, myCommand.getCommand("pause"));

	EntityManager::getInstance().setRenderWindowForDebug(getWindow());

	SoundManager::getInstance().playSound("8-bit-background", true);

}

void GameScene::updateControlKey() {
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("jump"), myCommand.getCommand("jump"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("left"), myCommand.getCommand("left"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("right"), myCommand.getCommand("right"));
	myKeyExecute.changeKey(GameConfig::getInstance().getControl("shoot"), myCommand.getCommand("shoot"));
	myKeyExecute.addCommand(GameConfig::getInstance().getControl("dodge"), myCommand.getCommand("dodge"));
}

void GameScene::update(float deltatime) {
	if (GameConfig::getInstance().levelStatus == FIRST_START) {
		currentLevel = GameConfig::getInstance().currentLevel;
		GameConfig::getInstance().levelStatus = PLAYING;
		restartLevel();
	}

	if (GameConfig::getInstance().hasKeyChanges) {
		GameConfig::getInstance().hasKeyChanges = false;
		updateControlKey();
	}



	if (deltatime > 0.3) deltatime = 0.3;
	myCommand.setDeltaTime(deltatime);
	myKeyExecute.handleInput();


	//if (GameConfig::getInstance().levelStatus == PAUSE) return;

	BACKGROUND_COLOR bgCol = GameConfig::getInstance().backgroundColor;
	if (bgCol == BLACK) getWindow()->clear(BLACK_BG);
	if (bgCol == BLUE) getWindow()->clear(BLUE_BG);

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
	camera->renderGameInfo(getWindow(), *FontManager::getInstance().getFont("Roboto").get(), GameConfig::getInstance(), myCommand);

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
	// check for level
	retrieveLevelStatus();
}