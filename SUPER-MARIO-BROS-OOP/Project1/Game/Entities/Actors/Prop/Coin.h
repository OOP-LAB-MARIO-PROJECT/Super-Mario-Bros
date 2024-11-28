#pragma once
#include "Collectable.h"
#include <vector>
#include <string>

class Coin : public Collectable {

	std::vector<std::string> animation;
	int aniloop;
	float timer;
public:

	Coin(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void touched(float deltatime) override;
	ENTITY_TYPE getType() override;
};
