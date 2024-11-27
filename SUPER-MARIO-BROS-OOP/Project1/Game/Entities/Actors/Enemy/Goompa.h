#ifndef _ENTITY_H_
#include "Enemy.h"
#define _ENTITY_H_
/*

simple testing enemy
*/

class Goompa : public Enemy
{
	int health = 1;
	int facing = 0;
public:
	
	Goompa(sf::Vector2f pos, sf::Vector2f size, Map* map);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void inflictDamage();

	ENTITY_TYPE getType() override;
};
#endif