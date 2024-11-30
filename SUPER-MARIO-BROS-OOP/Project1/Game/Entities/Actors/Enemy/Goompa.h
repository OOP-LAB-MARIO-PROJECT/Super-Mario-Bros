#pragma once
#include "Enemy.h"
#include <vector>
#include <map>
/*

simple testing enemy
*/
class Goompa : public Enemy
{
	int health = 1;
	int facing = 0;
	enum state {
		MOVE, DIE,
	} currentState;
	std::map <state, std::vector <std::string>> ani;
	float timer = 0;
	int aniLoop = 0;
	bool isDead = false;
	float deathTimer = 0;
public:
	
	Goompa(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void animation(float deltatime);
	void inflictDamage() override;
	void affectOther(Entity* other, float deltatime) override;

	ENTITY_TYPE getType() override;
};
