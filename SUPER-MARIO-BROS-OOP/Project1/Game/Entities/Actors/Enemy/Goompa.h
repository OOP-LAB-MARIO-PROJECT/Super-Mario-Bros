#pragma once
#include "Enemy.h"
#include <vector>
/*

simple testing enemy
*/
class Goompa : public Enemy
{
	int health = 1;
	int facing = 0;
	std::vector <std::string> animation;

public:
	
	Goompa(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void inflictDamage() override;

	ENTITY_TYPE getType() override;
};
