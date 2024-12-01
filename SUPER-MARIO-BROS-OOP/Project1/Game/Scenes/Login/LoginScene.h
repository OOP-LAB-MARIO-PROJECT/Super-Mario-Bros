#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/TextBox.h"
#include "../../../UI_Components/Animation.h"


class LoginScene : public Scene
{
private:
    sf::Text text;
    std::vector<TextBox> textBoxes;
    std::vector<Button> buttons;
    bool showInvalidMessage = false;
	sf::Texture titleTexture;
	sf::Sprite titleSprite;
	bool beingSelected;
    int currentBox;
    sf::RectangleShape shape;
    sf::Text inValid;
    sf::Texture pinkFlower;
	sf::Sprite pinkFlowerSprite1;
	sf::Sprite pinkFlowerSprite2;
	sf::Texture sadMarioTexture;
    sf::Sprite sadMarioSprite;

public:
    LoginScene(sf::RenderWindow* window);
    ~LoginScene() {
    };

    bool isValidAccount();
    void loopEvents();
    void drawLoginMenu();
    void drawInvalidArgument();
	void loadGif(float deltatime);
    void update(float deltatime) override;
};

