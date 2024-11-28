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
    //sf::Texture hoveredMarioTexture;
    //sf::Sprite idleMario;
    //sf::Texture idleMarioTexture;
	//bool isMarioHovered = false;   

    //used to render mario gif
	//std::shared_ptr<sf::Texture> marioTexture;
 //   sf::Vector2u imageCount; //to calculate to the size of a single sprite in a row and the number of row
 //   sf::Vector2u currentImage;
 //   float totalTime;    //the total time since we last changed image
 //   float switchTime; //the time it takes before switching to another image
public:
    //sf::IntRect rect; //used to display the animation

    HomeScene(sf::RenderWindow* window);
    ~HomeScene() {
    };
    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
    void render(float deltatime);
};