#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../Utils/TextureManager.h"
#include "../../../Utils/EntityManager.h"
#include "../../../Utils/FontManager.h"
#include "../../Control/CommandManager.h"
#include "../../Control/KeyExecute.h"

#include "../../Entities/Actors/Player.h"
#include "../../Entities/Map.h"
#include "Camera.h"

#include "../../Control/Commands/PlayerMovement.h"
#include "../../Control/Commands/GameControl.h"

#include "../../Scenes/Map/MapScene.h"
#include "../../GameConfig.h"

class GameScene : public Scene {

	Map* gameMap = NULL;
	Player* player = NULL;
	Camera* camera = NULL;

	CommandManager myCommand;
	KeyExecute myKeyExecute;
	std::map <std::string, std::string> levelMap;
	std::string currentLevel;
	std::vector<Button> buttons;

public:

	GameScene(sf::RenderWindow* window);
	~GameScene();

	void update(float deltatime) override;
	void updateControlKey();
	void nextLevel(std::string level);
	void retrieveLevelStatus();
	void restartLevel();
	void loadMapList();
};
