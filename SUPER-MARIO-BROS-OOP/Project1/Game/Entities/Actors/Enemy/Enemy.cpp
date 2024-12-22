#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _pos, sf::Vector2f _size) : Actor(_pos, _size) {
}


bool Enemy::getIsDeadByOtherEnemy() {
	return isDeadByOtherEnemy;
}


void Enemy::setIsDeadByOtherEnemy(bool a) {
	isDeadByOtherEnemy = a;
}
