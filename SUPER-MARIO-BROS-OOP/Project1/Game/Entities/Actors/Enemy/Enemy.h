#pragma once
#include "../Actor.h"
/*

	// set the map that the enemy are on
	Enemy(sf::Vector2f _pos, sf::Vector2f _size, Map* _map);

	// update in respect of time
	void update(float deltatime) = 0;

	// perform the behavior of an enemy
	virtual void behavior() = 0;

	// call the map-><function> to get info
*/

class Enemy : public Actor {
protected:
	bool isDeadByOtherEnemy = false;
public:

	Enemy(sf::Vector2f _pos, sf::Vector2f _size);
	virtual void update(float deltatime) override = 0;
	virtual void behavior(float detatime) = 0;
	bool getIsDeadByOtherEnemy() override;
	void setIsDeadByOtherEnemy(bool a) override;
};
