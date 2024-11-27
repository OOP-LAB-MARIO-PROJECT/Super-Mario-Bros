#include "MoveUpTile.h"

void MoveUpTile::setVel(sf::Vector2f vel) {
	Physics::setVel(vel);
	Entity::setVel(vel);
}


void MoveUpTile::touched(float deltatime) {
	if (isTouch) return;
	isTouch = true;
	setVel({ 0, -90 });
}

void MoveUpTile::destroy(float deltatime) {
	kill();
}

void MoveUpTile::update(float deltatime) {
	if (isTouch) setPos(getPos() + getVel() * deltatime);
	
	if (getPos().y > initpos.y) {
		isTouch = false;
		setVel(sf::Vector2f{ 0, 0 });
		setPos(initpos);
	}
	
	if (isTouch) performPhysics(deltatime);
}

MoveUpTile::MoveUpTile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans) : Tile(_pos, _size, isTrans), Physics({0, 0}, {0, 800}) {
	initpos = _pos;
}
