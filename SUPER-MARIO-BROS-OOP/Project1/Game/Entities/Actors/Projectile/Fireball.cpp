#include "Fireball.h"
#include <exception>

Fireball::Fireball() : Projectile() {
	throw std::exception("cannot create an projectile without position");
}

Fireball::Fireball(sf::Vector2f pos) {
	hitbox.size = sf::Vector2f(5, 5);
	isRenderHitbox = true;
}

Fireball::Fireball(sf::Vector2f pos, sf::Vector2f size, int facing) : Projectile(pos, size) {

	animation = {
		"fireball-0",
		"fireball-1",
		"fireball-2",
		"fireball-3"
	};

	setTexture("8-bit-block", animation[loop]);
	autoSpriteFollowHitbox = true;

	hitbox.size = size;
	hitbox.pos = pos;
	timeToLive = 10;
	if (facing == 1) setVel(sf::Vector2f(80, 0));
	if (facing == -1) setVel(sf::Vector2f(-80, 0));
	setGravity(sf::Vector2f(0, 400));
	setFric(sf::Vector2f(0, 0));
	isRenderHitbox = true;
	isRenderSprite = true;
}


void Fireball::update(float deltatime) {
	if ((timeToLive -= deltatime) <= 0) kill();
	timer -= deltatime;
	
	if (timer < 0) {
		loop++;
		if (loop >= animation.size()) loop = 0;
		timer = 0.2;
		setTexture(currentTexture, animation[loop]);
	}

	if (currentTexture == "item-object") return;

	for (auto en : otherEntities) if (en->getType() == ENEMY) {
		Collision::rect a = { en->getHitbox().pos, en->getHitbox().size };
		Collision::rect b = { this->getHitbox().pos, this->getHitbox().size };

		if (rectVsRect(a, b)) {
			en->setIsDeadByOtherThings(true);
			explode();
		}
	}

	int dir = resolveCollideGround(obstacle, deltatime);
	if (dir & 5) setVel(sf::Vector2f(getVel().x, -100));
	if (dir & 10) explode();

	setPos(getPos() + getVel() * deltatime);
	performPhysics(deltatime);
}

void Fireball::explode() {
	timeToLive = 0.5;
	loop = 0;
	animation = {
		"fire-boom-0",
		"fire-boom-1",
		"fire-boom-2"
	};
	currentTexture = "item-object";
	setTexture(currentTexture, animation[loop]);
}