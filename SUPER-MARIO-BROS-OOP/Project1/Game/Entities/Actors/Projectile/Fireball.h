#pragma once
#include "Projectile.h"
#include "../../../../Utils/EntityManager.h"
class Fireball : public Projectile {
	int affectType = ENEMY;
	float timeToLive = 0;
public: 
	Fireball();
	Fireball(sf::Vector2f pos);
	Fireball(sf::Vector2f pos, sf::Vector2f size, int facing);
	void update(float deltatime) override;
};

