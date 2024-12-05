#include "Mushroom.h"

RedMushroom::RedMushroom(sf::Vector2f _pos, sf::Vector2f _size) : Collectable(_pos, sf::Vector2f(14, 16)) {
	isRenderHitbox = false;
	isRenderSprite = true;
	setTexture("item-object", "red-mushroom-0");
	score = 200;
}

int RedMushroom::getType() {
	return RED_MUSHROOM;
}

void RedMushroom::update(float deltatime) {
	if (dist < 10.f) {
		setVel({ 0, -7 });
		dist += 7 * deltatime;
		setPos(getPos() + getVel() * deltatime);		
		return;
	}

	for (auto en : otherEntities) if (en->getType() == TILE) {
		Hitbox ob = en->getHitbox();
		ob.vel = sf::Vector2f{ 0.f, 0.f };
		obstacle.push_back(ob);
	}

	int dir = resolveCollideGround(obstacle, deltatime);
	setPos(getPos() + getVel() * deltatime);  //update right after collision for best resolution


	if (dir & (1 << 2)) setVel({ getVel().x, 0 });
	if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(50, getVel().y));
	if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-50, getVel().y));

	if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
		if (facing == 1)
			setVel(sf::Vector2f(50, getVel().y));
		else
			setVel(sf::Vector2f(-50, getVel().y));
	}

	// 1 << 1 = left 
	behavior(deltatime);
	performPhysics(deltatime);
}

void RedMushroom::behavior(float detatime) {
}

void RedMushroom::touched(float detatime) {
	kill();
	GameConfig::getInstance().addScore(score);
	GameConfig::getInstance().marioState = BIG;
}

void RedMushroom::affectOther(Entity* other, float deltateim) {
	touched(deltateim);
}


int GreenMushroom::getType() {
	return GREEN_MUSHROOM;
}

GreenMushroom::GreenMushroom(sf::Vector2f pos, sf::Vector2f size) : RedMushroom(pos, size) {
	setTexture("item-object", "green-mushroom-0");
}