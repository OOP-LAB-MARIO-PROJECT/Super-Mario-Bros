#pragma once
#include "../Scene.h"
#include "../../../UI/MainMenu.h"

class HomeScene : public Scene
{
public:
	HomeScene(sf::RenderWindow* window) : Scene(window) {};
	void update(float deltatime) override;
};

