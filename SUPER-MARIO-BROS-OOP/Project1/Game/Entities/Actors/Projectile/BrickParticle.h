#pragma once
#include "Projectile.h"
#include "../../Utils/EntityManager.h"
class BrickParticle : public Projectile {
	float timeToLive = 0;

	std::vector <std::string> animation;
	int loop = 0;
	float aniLoop = 0;
public:
	BrickParticle();
	BrickParticle(sf::Vector2f pos); 
	BrickParticle(sf::Vector2f pos, sf::Vector2f size, int facing);
	void update(float deltatime) override;
};

