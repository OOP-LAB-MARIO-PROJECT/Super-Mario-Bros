#include "Tile.h"

Tile::Tile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans) : Entity() {
	pos = _pos;
	size = _size;
	isTransparent = isTrans;

	m_hitbox.setPosition(pos);
	m_hitbox.setSize(size);

	sprite.setPosition(pos);

	m_hitbox.setFillColor(sf::Color::Magenta);
	m_hitbox.setOutlineColor(sf::Color::Blue);
	m_hitbox.setOutlineThickness(1);
};


Hitbox Tile::getHitbox() {
	return { pos, size, sf::Vector2f{0.f, 0.f} };
}


void Tile::setPosition(sf::Vector2f _pos) {
	m_hitbox.setPosition(_pos);
	pos = _pos;
}

void Tile::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Tile::render(sf::RenderWindow* window) const {
	if (isRenderHitbox)
		window->draw(m_hitbox);
	if (isRenderSprite)
		window->draw(sprite);
}


void Tile::setTexture(const std::string& sourceName, const std::string& rectName) {
	TextureManager::getInstance().setTextureRect(sprite, sourceName, rectName);
}

ENTITY_TYPE Tile::getType() {
	return currentType;
}



sf::Vector2f Tile::getPos() const {
	return pos;
}
// set srite and hitbox pos
void Tile::setPos(sf::Vector2f pos) {
	setPosition(pos);
	setSpritePos(pos);
}
