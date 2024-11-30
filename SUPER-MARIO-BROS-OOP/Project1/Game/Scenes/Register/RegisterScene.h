#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/TextBox.h"


class RegisterScene : public Scene
{
private:
    sf::Text text;
    std::vector<TextBox> textBoxes;
    std::vector<Button> buttons;
    bool showInvalidMessage = false;
    bool isValidMessage;
	sf::Text inValid;
	sf::RectangleShape shape;
public:
    RegisterScene(sf::RenderWindow* window);
    ~RegisterScene() {
    };

    void addLineIfNotExists();
    void loopEvents();
    void drawLoginMenu();
    void drawArgument();
    void update(float deltatime) override;
};

