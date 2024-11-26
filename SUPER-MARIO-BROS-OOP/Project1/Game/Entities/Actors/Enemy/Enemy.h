#pragma once
#include "../Actor.h"
#include "../../Map.h"
#include <iostream>
/*

	// set the map that the enemy are on
	Enemy(sf::Vector2f _pos, sf::Vector2f _size, Map* _map);

	// update in respect of time
	void update(float deltatime) = 0;

	// perform the behavior of an enemy
	virtual void behavior() = 0;

	// call the map-><function> to get info
*/

class Enemy : public Actor
{
protected:
	int facing = 1;
	Map* map = NULL;

public:

	Enemy(sf::Vector2f _pos, sf::Vector2f _size, Map* _map);

	virtual void update(float deltatime) = 0;
	virtual void behavior(float detatime) = 0;
};
