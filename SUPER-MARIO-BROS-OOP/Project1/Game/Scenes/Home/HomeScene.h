#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/Animation.h"
class HomeScene : public Scene
{
    std::vector<Button> buttons;
    std::vector<Animation> animations;
	std::vector<std::shared_ptr<sf::Sprite>> sprites; //for animation sprite
	sf::Texture goombaTexture;
	sf::Sprite goombaSprite;


public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };
    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
    void loadGif(float deltatime);
};