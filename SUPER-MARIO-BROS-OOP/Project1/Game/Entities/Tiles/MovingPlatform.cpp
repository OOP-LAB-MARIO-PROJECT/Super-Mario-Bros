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
}

void MovingPlatform::affectOther(Entity* other) {
	sf::Vector2f pos = other->getHitbox().pos;
	sf::Vector2f size = other->getHitbox().size;
	sf::Vector2f vel = other->getHitbox().vel;

}

ENTITY_TYPE MovingPlatform::getType() {
	return TILE;
}

Hitbox MovingPlatform::getHitbox() {
	return hitbox;
}