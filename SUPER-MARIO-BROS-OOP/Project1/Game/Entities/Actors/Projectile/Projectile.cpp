#include "Projectile.h"
Projectile::Projectile() {
	hitbox = {
		sf::Vector2f(0, 0),
		sf::Vector2f(0, 0),
		sf::Vector2f(0, 0)
	};
}

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size) {
	hitbox.pos = pos; hitbox.size = size;
}

void Projectile::update(float deltatime) {}
