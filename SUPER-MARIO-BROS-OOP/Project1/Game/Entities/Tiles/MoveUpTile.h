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
	void update(float deltatime) override;
	void destroy(float deltatime) override;
	void touched(float deltatime) override;
};

