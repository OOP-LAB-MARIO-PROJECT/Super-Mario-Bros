#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _pos, sf::Vector2f _size) : Actor(_pos, _size), collectable(nullptr) {
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

void Enemy::setCollectable(Collectable* _collectable) {
	collectable = _collectable;
}

void Enemy::update(float deltaTime) {
	checkIfDead();
}