#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _pos, sf::Vector2f _size) : Actor(_pos, _size) {
}


bool Enemy::getIsDeadByOtherThings() {
	return isDeadByOtherThings;
}


void Enemy::setIsDeadByOtherThings(bool a) {
	isDeadByOtherThings = a;
}


bool Enemy::getIsAttack() {
	return isAttack;
}