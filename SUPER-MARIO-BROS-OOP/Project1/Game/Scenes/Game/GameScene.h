#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../Utils/TextureManager.h"
#include "../../../Utils/EntityManager.h"
#include "../../Control/CommandManager.h"
#include "../../Control/KeyExecute.h"

#include "../../Entities/Actors/Player.h"
#include "../../Entities/Map.h"
#include "Camera.h"

#include "../../Control/Commands/PlayerMovement.h"

class GameScene : public Scene {

	Map* gameMap = NULL;
	Player* player = NULL;
	Camera* camera = NULL;
	CommandManager myCommand;
	KeyExecute myKeyExecute;

public:

	GameScene(sf::RenderWindow* window);
	~GameScene();
	void update(float deltatime) override;
};
