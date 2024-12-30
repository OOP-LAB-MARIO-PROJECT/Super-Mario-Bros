#pragma once
#include "Projectile.h"
#include "../../../../Utils/EntityManager.h"
class Fireball : public Projectile {
	int affectType = ENEMY;
	float timeToLive = 0;
	float timer = 0;
	std::vector <std::string> animation;
	int loop = 0;
	std::string currentTexture = "8-bit-block";

public: 
	Fireball();
	Fireball(sf::Vector2f pos);
	Fireball(sf::Vector2f pos, sf::Vector2f size, int facing);
	void explode();
	void update(float deltatime) override;
};

