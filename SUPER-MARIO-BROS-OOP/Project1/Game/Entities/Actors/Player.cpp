#include "Player.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size, Map* map) : Actor(pos, size), map(map) {
	isRenderSprite = true;
	isRenderHitbox = true;

	setTexture("mario", "right-small-mario-1");
}


void Player::update(float deltatime) {


	if (facing == 0)
		setVel({ 0, getVel().y });


	sf::Vector2f vx = getVel();
	int isCollide = resolveCollideGround(map->getNearTiles(getPos()), deltatime);

	if (getPos().y > 800) setVel(sf::Vector2f(getVel().x, 0));
	//if (isCollide) std::cout << "collidiing!!!!!!!1\n";
	isOnGround = isCollide & (1 << 2);

	if (isOnGround)
		setFric({ 15, 0 }), isJumping = false;
	else
		setFric({ 0, 0 });

	setPos(getPos() + getVel() * deltatime);
	setSpritePos(getPos() - sf::Vector2f{ 2, 2 });

	if (isCollide & 5) // touch top or bottom
		setVel({ getVel().x, 0 }), isJumping = false;
	if (!isOnGround) setVel({ getVel().x / 4, getVel().y });

	performPhysics(deltatime);
}

void Player::jump(float deltatime) {
	if (isOnGround && !isJumping) {
		setVel({ getVel().x, -190 });
		isOnGround = false;
		reachMaxHeight = false;
		isJumping = true;
	}
	else if (isJumping) {
		if (reachMaxHeight) return;
		sf::Vector2f newVel = getVel();
		newVel += sf::Vector2f(0, -40000) * deltatime;
		if (newVel.y < -198.f)
			newVel.y = -198.f, reachMaxHeight = true;
		setVel(newVel);
	}
}

void Player::notJump(float deltatime) {
	if (!isJumping) return;
	isJumping = false;
	//reachMaxHeight = true;
	setVel({ getVel().x, getVel().y / 3 });
}

void Player::moveLeft(float deltatime) {
	facing = -1;
	setVel({ -140, getVel().y });
}

void Player::moveRight(float deltatime) {
	facing = 1;
	setVel({ 140, getVel().y });
}