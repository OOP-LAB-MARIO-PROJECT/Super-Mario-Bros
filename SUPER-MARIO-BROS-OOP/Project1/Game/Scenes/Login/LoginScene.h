#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"
#include "../../../UI_Components/TextBox.h"


class LoginScene : public Scene
{
private:
    sf::Text text;
    std::vector<TextBox> textBoxes;
    std::vector<Button> buttons;
    bool showInvalidMessage = false;
public:
    LoginScene(sf::RenderWindow* window);
    ~LoginScene() {
    };

    bool isValidAccount();
    void loopEvents();
    void drawLoginMenu();
    void drawInvalidArgument();
    void update(float deltatime) override;
};

