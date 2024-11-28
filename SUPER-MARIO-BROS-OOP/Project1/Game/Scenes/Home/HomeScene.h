#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/Animation.h"
class HomeScene : public Scene
{
    std::vector<Button> buttons;
	Animation marioAnimation;
    std::shared_ptr<sf::Texture> marioTexture = nullptr;
	std::shared_ptr<sf::Sprite> marioSprite = nullptr;
public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };
    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
    void render(float deltatime);
};