#pragma once
#include "../Scene.h"	
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include <iostream>
#include <map>

class SettingScene : public Scene
{
	std::vector<Button> buttons;
	sf::Font font;
	bool isMute = false;
	float volume;
	bool save = false;
	std::map<std::string, sf::Keyboard::Key> keys;

public:
	SettingScene(sf::RenderWindow* window);
	~SettingScene() {
	};
	void changeVolume();
	void saveSetting();
	void changeKeys();
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};