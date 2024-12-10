#pragma once
#include "../Scene.h"	
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
#include "../../../UI_Components/VolumeSlider.h"
#include "../../../UI_Components/Animation.h"

class SettingScene : public Scene
{
	std::vector<Button> buttons;
	/*sf::Font font;*/
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