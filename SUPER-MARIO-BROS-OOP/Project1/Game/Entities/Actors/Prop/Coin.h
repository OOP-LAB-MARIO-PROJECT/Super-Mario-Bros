#pragma once
#include "Collectable.h"
#include <vector>
#include <string>

class Coin : public Collectable {

	std::vector<std::string> animation;
	int aniloop;
	float timer;
	float fallingTimer = 0;
	bool isInstantPoint = false;
	bool isTouch = false;
	
public:

	Coin(sf::Vector2f pos, sf::Vector2f size, bool instant = false);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void touched(float deltatime) override;
	void affectOther(Entity* other, float deltatime) override;
	int getType() override;
};
