#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"

class HomeScene : public Scene
{
    std::vector<Button> buttons;
    sf::Sprite hoveredMario;
    sf::Texture hoveredMarioTexture;
    sf::Sprite idleMario;
    sf::Texture idleMarioTexture;
	bool isMarioHovered = false;    
public:
    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };
    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
};