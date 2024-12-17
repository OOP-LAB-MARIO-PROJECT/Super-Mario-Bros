#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include <string>
#include <vector>
#include <fstream>
#include "../../GameConfig.h"
class MapScene : public Scene
{
	GameConfig* gameConfig = nullptr;
	std::vector<std::string> allMapNames;
	std::vector<std::string> unlockedMapNames;
	std::vector<sf::RectangleShape> shapes;
	std::vector<sf::Text> texts;

public:
	MapScene(sf::RenderWindow* window);
	~MapScene() {

	};
	std::string getMapName();
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};

