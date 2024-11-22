#pragma once
#include "../Scene.h"
#include "../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"

class HomeScene : public Scene
{
    std::vector<Button> buttons;
    std::vector<std::string> options;
    std::vector<sf::Text> texts;
    sf::Font font;
    std::vector<sf::Vector2f> textPositions;
    std::vector<sf::Vector2f> buttonPositions;

public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };


    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
};