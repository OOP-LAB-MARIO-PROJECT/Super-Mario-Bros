#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include <string>
#include <map>
#include <fstream>
#include "../../../UI_Components/Button.h"
#include "../../GameConfig.h"
class MapScene : public Scene
{
	GameConfig* gameConfig = nullptr;
	std::map<std::string, bool> allMapNames;
	std::vector<std::string> unlockedMapNames;
	std::vector<Button> buttons;
	std::vector<bool> disabled;
	std::vector<sf::Text> texts;

public:
	MapScene(sf::RenderWindow* window);
	~MapScene() {

	};
	bool isUnlocked(std::string mapName);
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};

