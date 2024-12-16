#include "BrickParticle.h"
#include <exception>

BrickParticle::BrickParticle() : Projectile() {
	throw std::exception("cannot create an projectile without position");
}

BrickParticle::BrickParticle(sf::Vector2f pos) {
	hitbox.size = sf::Vector2f(5, 5);
	//isRenderHitbox = true;
}

BrickParticle::BrickParticle(sf::Vector2f pos, sf::Vector2f size, int facing) : Projectile(pos, size) {
	hitbox.size = size;
	hitbox.pos = pos;
	timeToLive = 1;
	isRenderSprite = true;

	animation = {
		"brick-particle-0",
		"brick-particle-1",
		"brick-particle-2",
		"brick-particle-3"
	};

	needUpdateEnvironment = false;
	if (facing == 1) setVel(sf::Vector2f(80, -100));
	if (facing == -1) setVel(sf::Vector2f(-80, -100));
	setGravity(sf::Vector2f(0, 400));
	setFric(sf::Vector2f(0, 0));
	setTexture("8-bit-block", animation[loop % 4]);
	//isRenderHitbox = true;
}


void BrickParticle::update(float deltatime) {
	if ((timeToLive -= deltatime) <= 0) kill();
	aniLoop -= deltatime;
	if (aniLoop <= 0) loop++, aniLoop = 0.1;

	setTexture("8-bit-block", animation[loop % 4]);
	setPos(getPos() + getVel() * deltatime);
	performPhysics(deltatime);
}