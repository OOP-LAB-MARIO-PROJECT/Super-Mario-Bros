#include "MovingPlatform.h"


MovingPlatform::MovingPlatform(sf::Vector2f pos, sf::Vector2f size, bool isTrans, std::string properties) : Tile(pos, sf::Vector2f(16, 8), false) {
	vel.y = -16;
	vel.x = 0;

	hitbox.size = sf::Vector2f(16, 8);

	setRenderSprite(true);
	setTexture("item-object", "moving-platform-0");
	int p[] = { 0, 0, 0, 0 };
	int id = 0;
	for (char ch : properties) if (ch == ';') id++;
	else p[id] = p[id] * 10 + ch - '0';

	float distance = p[0] - p[1];
	if (distance < 0)
		vel = -vel;

	isUp = true;
	if (p[2] == 1) // verticle movement
		start = sf::Vector2f(pos.x, p[0]), end = sf::Vector2f(pos.x, p[1]);

	if (p[2] == 2) // horizontal
		start = sf::Vector2f(p[0], pos.y), end = sf::Vector2f(p[1], pos.y), std::swap(vel.x, vel.y), isUp = false;

	if (p[3] == 1) isMoveBack = true; else isMoveBack = false;

	this->hitbox.vel = vel;

	//setPos(start);
}

void MovingPlatform::update(float deltatime) {
	sf::Vector2f before = end - getPos();
	setPos(getPos() + vel * deltatime);
	sf::Vector2f after = end - getPos();

	float a = before.x * before.x + before.y * before.y;
	float b = after.x * after.x + after.y * after.y;

	if (b > a) {
		std::cout << isMoveBack << '\n';
		if (isMoveBack) {
			std::swap(start, end);
			vel = -vel;
			setVel(vel);
		}
		setPos(start);

	}

	hitbox.pos = getPos();

	if (player == NULL) return;
	Hitbox pHitbox = player->getHitbox();

	Collision::rect this_rect = { this->getHitbox().pos, this->getHitbox().size };
	Collision::rect player_rect = { player->getHitbox().pos, player->getHitbox().size };

	if (!rectVsRect(this_rect, player_rect)) return;

	if (pHitbox.pos.y + pHitbox.size.y >= this->getHitbox().pos.y) {
		float contactLen = pHitbox.pos.y + pHitbox.size.y - this->getHitbox().pos.y;
		sf::Vector2f newVel = player->getHitbox().vel;
		newVel.y = contactLen;
		player->setVel(newVel);
		pHitbox.pos.y -= contactLen;
		player->setPos(pHitbox.pos);
	}
	std::cout << "asdfasdf\n";
	pHitbox = player->getHitbox();
	pHitbox.vel.x += this->getHitbox().vel.x;
	player->setVel(pHitbox.vel);
}

void MovingPlatform::affectOther(Entity* other, float deltatime) {
	if (other->getType() != PLAYER) return;
	player = other;
	sf::Vector2f playerVel = other->getHitbox().vel;
	playerVel.x += this->getHitbox().vel.x;
}

ENTITY_TYPE MovingPlatform::getType() {
	return TILE;
}

Hitbox MovingPlatform::getHitbox() {
	hitbox.vel = vel;
	return hitbox;
}