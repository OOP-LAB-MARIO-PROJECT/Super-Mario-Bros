#include "Enemy.h"

Enemy::Enemy(sf::Vector2f _pos, sf::Vector2f _size, Map* _map) : Actor(_pos, _size), map(_map) {
}
