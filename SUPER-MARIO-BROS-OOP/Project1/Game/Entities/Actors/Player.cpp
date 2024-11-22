#include "Player.h"

Player::Player(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size) {
	isRenderSprite = true;
	isRenderHitbox = true;
}


void Player::update(float deltatime) {

}

void Player::jump(float deltatime) {
	setVel(sf::Vector2f(getVel().x, 340.f));
}

void Player::notJump(float deltatime) {
}

void Player::moveLeft(float deltatime) {
	facing = -1;
}

void Player::moveRight(float deltatime) {
	facing = 1;
}