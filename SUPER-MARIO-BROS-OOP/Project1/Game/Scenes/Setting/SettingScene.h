#pragma once
#include "../../../UI_Components/VolumeSlider.h"
#include "../../../UI_Components/Animation.h"
#include "../../../UI_Components/Button.h"
#include "../../../Utils/SceneManager.h"
#include "../../GameConfig.h"
#include <SFML/Audio.hpp>
#include "../Scene.h"	
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>

class SettingScene : public Scene
{
	std::vector<Button> buttons;
	bool isMute = false;
	float volume = 50.0;
	bool save = false;
	std::map<std::string, sf::Keyboard::Key> keys;
	VolumeSlider volumeSlider;
	sf::Text volumeText;

	std::shared_ptr<sf::Texture> muteIconTexture;
	std::shared_ptr<sf::Texture> unmuteIconTexture;
	sf::Sprite muteIconSprite;
	sf::Sprite unmuteIconSprite;

	std::shared_ptr<sf::Texture> luigiTexture;
	sf::Sprite luigiSprite;


	std::vector<Animation> animations;
	std::vector<std::shared_ptr<sf::Sprite>> sprites;
	sf::Sprite talkingFlowerSprite;

	std::shared_ptr<sf::Texture> wrenchTexture;
	sf::Sprite wrenchSprite;
	std::shared_ptr<sf::Texture> backTexture;
	sf::Sprite backSprite;
	bool isHovered;
	int currentButton = 0;

public:
	SettingScene(sf::RenderWindow* window);
	~SettingScene() {
	};
	void muteHandling();
	void changeVolume();
	void loadGif(float deltatime);
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};