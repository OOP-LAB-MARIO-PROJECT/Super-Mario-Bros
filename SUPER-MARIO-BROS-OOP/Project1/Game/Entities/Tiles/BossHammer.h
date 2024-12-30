#pragma once
#include "../../GameConfig.h"
#include "Tile.h"

class BossHammer : public Tile {
private:
public:
	BossHammer(sf::Vector2f pos, sf::Vector2f size, bool isTrans);
	int getType() override;
	void affectOther(Entity* other, float deltatime) override;
	void update(float deltatime) override;
};
