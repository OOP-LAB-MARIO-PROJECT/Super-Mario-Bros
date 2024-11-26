#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>


class	Camera {
private:
	sf::View camera;
	float leftLimit;
	float rightLimit;
	float aboveLimit;
	float beneathLimit;
	float base;

public:
	Camera(sf::RenderWindow* w, sf::Vector2f ppos);
	void moveCamera(const float& x, const float& y);
	void setCameraView(sf::RenderWindow* w);
	void followPlayer(const float& x, const float& y, const float& w, const float& h);
};