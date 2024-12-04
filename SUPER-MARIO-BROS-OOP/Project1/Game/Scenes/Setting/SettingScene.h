#pragma once
#include "../Scene.h"	
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <map>
#include "../../../UI_Components/VolumeSlider.h"

class SettingScene : public Scene
{
	std::vector<Button> buttons;
	sf::Font font;
	bool isClicked = false;
	float volume = 50.0;
	bool save = false;
	std::map<std::string, sf::Keyboard::Key> keys;
	VolumeSlider volumeSlider;
public:
	SettingScene(sf::RenderWindow* window);
	~SettingScene() {
	};
	void muteHandling();
	void changeVolume();
	void saveSetting();
	void changeKeys();
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};