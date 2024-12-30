#pragma once
#include <SFML/Graphics.hpp>
#include "../../GameConfig.h"
#include "../../../UI_Components/Button.h"
#include "../../../Utils/SceneManager.h"
#include "../../../Game/Control/CommandManager.h"
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>

class	Camera {
private:
	sf::View camera;
	float leftLimit;
	float rightLimit;
	float aboveLimit;
	float beneathLimit;
	float base;
	float width = 400;
	float height = 240;
	std::string pausText = "Pausing";
	float pauseTimer = 0;
	Button backhome;

public:
	Camera(sf::RenderWindow* w, sf::Vector2f ppos);
	void moveCamera(const float& x, const float& y);
	void setCameraView(sf::RenderWindow* w);
	void followPlayer(const float& x, const float& y, const float& w, const float& h);
	void renderGameInfo(sf::RenderWindow* window, sf::Font& font, const GameConfig& config, CommandManager& command);
	std::pair <sf::Vector2f, sf::Vector2f> getRenderSpace();
};