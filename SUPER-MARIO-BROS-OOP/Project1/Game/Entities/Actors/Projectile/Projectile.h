#pragma once
#include "../Actor.h"

class Projectile : public Actor {
public:
	Projectile();
	Projectile(sf::Vector2f pos, sf::Vector2f size);
	virtual void update(float deltatime) override;
};

