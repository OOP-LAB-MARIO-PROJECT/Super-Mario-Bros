
#pragma once

#include "../Actor.h"
#include <iostream>
/*

	 set the map that the enemy are on
	Enemy(sf::Vector2f _pos, sf::Vector2f _size, Map* _map);

	 update in respect of time
	void update(float deltatime) = 0;

	 perform the behavior of an enemy
	virtual void behavior() = 0;

	 call the map-><function> to get info
*/

class Collectable : public Actor
{
protected:
	int facing = 1;
	
public:
	int score = 0;
	Collectable(sf::Vector2f _pos, sf::Vector2f _size);

	virtual void update(float deltatime) override = 0;
	virtual void behavior(float detatime) = 0; 
};

