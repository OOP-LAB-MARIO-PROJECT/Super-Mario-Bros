#pragma once
#include "../../../Utils/SceneManager.h"
#include "../../GameConfig.h"
#include <vector>
#include "../../../UI_Components/TextBox.h"
#include "../Scene.h"
class KeyBindingScene : public Scene
{
	std::vector<TextBox> textBoxes;
	std::vector<sf::RectangleShape> shapes;
	std::vector<sf::Text> actions;
	GameConfig* gameConfig = nullptr;
	bool beingSelected;
public:
	KeyBindingScene(sf::RenderWindow* window);
	~KeyBindingScene() {
	};
	void drawScene();
	void loopEvents();
	void update(float deltatime) override;
};

