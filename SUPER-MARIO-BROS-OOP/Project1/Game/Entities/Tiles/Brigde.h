#pragma once
#include "../../GameConfig.h"
#include "Tile.h"

class Brigde : public Tile {
private:
	float timer = 0;
	bool isFirstUpdate = false;
public:
	Brigde(sf::Vector2f pos, sf::Vector2f size, bool isTrans);
	int getType() override;
	void update(float deltatime) override;
};
