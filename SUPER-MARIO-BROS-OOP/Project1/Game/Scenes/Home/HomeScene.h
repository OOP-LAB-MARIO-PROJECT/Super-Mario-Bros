#pragma once
#include "../Scene.h"
#include "../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"

class HomeScene : public Scene
{
    std::vector<Button> buttons;
public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };


    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
};