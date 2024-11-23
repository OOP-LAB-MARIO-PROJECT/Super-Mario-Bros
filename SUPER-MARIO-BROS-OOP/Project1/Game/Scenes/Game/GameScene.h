#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../Entities/Actors/Player.h"
#include "../../Entities/Map.h"
#include "Camera.h"

class GameScene : public Scene {

	Map* gameMap = NULL;
	Player* player = NULL;
	Camera* camera = NULL;

public:

	GameScene(sf::RenderWindow* window);
	~GameScene();
	void update(float deltatime) override;
};
