#include "Tile.h"

Tile::Tile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans) {
	pos = _pos;
	size = _size;
	isTransparent = isTrans;

	hitbox.setPosition(pos);
	hitbox.setSize(size);

	sprite.setPosition(pos);

	hitbox.setFillColor(sf::Color::Magenta);
	hitbox.setOutlineColor(sf::Color::Blue);
	hitbox.setOutlineThickness(1);
};


sf::RectangleShape& Tile::getHitbox() {
	return hitbox;
}


void Tile::setPosition(sf::Vector2f pos) {
	hitbox.setPosition(pos);
}

void Tile::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Tile::render(sf::RenderWindow* window) const {
	if (isRenderHitbox)
		window->draw(hitbox);
	if (isRenderSprite)
		window->draw(sprite);
}
