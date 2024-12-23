#pragma once
#include "Collectable.h"

class CastleGate : public Collectable {
	std::string nxt;
public:
	CastleGate(sf::Vector2f pos, sf::Vector2f size, std::string nextLevel);
	void update(float deltatime) override {};
	void behavior(float deltatime) override {};
	void touched(float deltatime) override;
	void affectOther(Entity* other, float deltatime) override;
	int getType() override;
};

