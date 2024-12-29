#pragma once
#include "../Scene.h"
#include "../../../Utils/SceneManager.h"
#include "../../GameConfig.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "../../../UI_Components/TextBox.h"
#include "../../../UI_Components/Button.h"

class KeyBindingScene : public Scene
{
	std::vector<TextBox> textBoxes;
	//std::vector<sf::RectangleShape> shapes;
	std::vector<std::shared_ptr <sf::Sprite>> sprites;
	sf::Texture upArrowTexture;
	sf::Sprite upArrowSprite;
	sf::Texture downArrowTexture;
	sf::Sprite downArrowSprite1;
	sf::Sprite leftArrowSprite2;
	sf::Texture leftArrowTexture;
	sf::Sprite leftArrowSprite;
	sf::Texture rightArrowTexture;
	sf::Sprite rightArrowSprite;
	sf::Texture jellyTexture;
	sf::Sprite jellySprite;
	sf::Texture fooTexture;
	sf::Sprite fooSprite;
	std::shared_ptr<sf::Texture> backTexture;
	sf::Sprite backSprite;

	std::vector<sf::Text> actions;
	std::vector<std::string> actualActions;
	std::vector<Button> buttons;
	GameConfig* gameConfig = nullptr;
	bool beingSelected;
	bool isInvalid = false;
public:
	KeyBindingScene(sf::RenderWindow* window);
	~KeyBindingScene() {
	};
	void drawScene();
	void loopEvents();
	sf::Keyboard::Key charToKey(char c);
	void update(float deltatime) override;
};
