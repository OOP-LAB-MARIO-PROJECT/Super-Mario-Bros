#include "Collectable.h"
Collectable::Collectable(sf::Vector2f _pos, sf::Vector2f _size) : Actor(_pos, _size) {
	isRenderHitbox = true;
	isRenderSprite = true;
}
