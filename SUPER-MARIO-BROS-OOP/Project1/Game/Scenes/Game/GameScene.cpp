#include "GameScene.h"

GameScene::~GameScene() {
	delete player;
	delete gameMap;
	delete camera;
}

GameScene::GameScene(sf::RenderWindow* window) : Scene(window) {
	// INITIALIZE 
	player = new Player(sf::Vector2f(50, 50), sf::Vector2f(14, 14));
	gameMap = new Map();
	gameMap->loadMap("Assets/Map/map.tsx", player);
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
}