#pragma once
#include "Tile.h"
#include "../../Utils/EntityManager.h"
class Flag : public Tile {
	bool isEnd = false;
public:
	bool isGodown = false;
	Flag(sf::Vector2f pos);
	void update(float deltaTime) override;
};

class Poll : public Tile {
	bool _touched = false;
public:

	bool isTouch();
	void touched(float deltatime) override;
	Poll(sf::Vector2f pos, sf::Vector2f size, bool isTrans);
	void affectOther(Entity* other, float deltatime) override;
};

class FullFlag : public Tile {
	std::vector <Poll*> poll;
	Flag* flag = NULL;
	bool isPollTouch = false;

public:
	FullFlag(sf::Vector2f pos);
	void update(float deltatime) override;
};
