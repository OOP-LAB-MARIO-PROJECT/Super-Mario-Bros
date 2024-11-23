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
	camera = new Camera(window);
	gameMap->loadMap("Assets/Map/map.txt", player);
}


void GameScene::update(float deltatime) {

	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
	}

	gameMap->update(deltatime, player->getPos(), player->getSize(), player->getVel());
	player->update(deltatime);

	camera->followPlayer(player->getPos().x, player->getPos().y, player->getSize().x, player->getSize().y);
	camera->setCameraView(getWindow());


	player->render(getWindow());
	gameMap->render(getWindow());
}