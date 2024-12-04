#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/Animation.h"
class HomeScene : public Scene
{
    std::vector<Button> buttons;
    std::vector<Animation> animations;
	std::vector<std::shared_ptr<sf::Sprite>> sprites; 
	sf::Sprite goombaSprite;
	sf::Texture startTexture;
	sf::Sprite startSprite;
	sf::Texture exitTexture;
	sf::Sprite exitSprite;
	sf::Texture settingTexture;
	sf::Sprite settingSprite;
	sf::Texture pipeTexture;
	sf::Sprite leftPipeSprite1; 	//have not been refactored
	sf::Sprite leftPipeSprite2;
	sf::Sprite leftPipeSprite3;
	sf::Sprite rightPipeSprite1;
	sf::Sprite rightPipeSprite2;
	sf::Sprite rightPipeSprite3;
	bool isMoonHovered;
	int currentMoon;

public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };
    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
    void loadGif(float deltatime);
};