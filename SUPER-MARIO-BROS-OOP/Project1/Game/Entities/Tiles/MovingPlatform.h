#pragma once
#include "../../GameConfig.h"
#include "Tile.h"

class MovingPlatform : public Tile {
private:
	sf::Vector2f start;
	sf::Vector2f end;
	sf::Vector2f vel;
	int isUp = true;
	bool isMoveBack = true;
	Entity* player = NULL;

public:
	MovingPlatform(sf::Vector2f pos, sf::Vector2f size, bool isTrans, std::string properties);
	ENTITY_TYPE getType() override;
	void affectOther(Entity* other, float deltatime) override;
	Hitbox getHitbox() override;
	void update(float deltatime) override;
};

