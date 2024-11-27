#pragma once
#include "Tile.h"
#include "../../Components/Physics.h"
class MoveUpTile : public Tile, public Physics {
protected:
	int state = 0;
	int timer = 0;
	bool isTouch = 0;
	sf::Vector2f initpos;
public:

	MoveUpTile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans = true);
	virtual void update(float deltatime) override;
	virtual void destroy(float deltatime) override;
	virtual void touched(float deltatime) override;
};

