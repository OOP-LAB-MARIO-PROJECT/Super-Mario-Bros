#include "Tile.h"

Tile::Tile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans) : Entity() {
	pos = _pos;
	size = _size;
	isTransparent = isTrans;
	currentType = TILE;
	if (isTrans) currentType = TRANS;
	

	sprite.setPosition(pos);
};


Hitbox Tile::getHitbox() {
	return { pos, size, sf::Vector2f{0.f, 0.f} };
}


void Tile::setPosition(sf::Vector2f _pos) {
	pos = _pos;
}

void Tile::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Tile::render(sf::RenderWindow* window) const {
	if (isRenderHitbox) {
		sf::VertexArray box(sf::LineStrip, 5);
		float x = pos.x, y = pos.y;
		float width = size.x, height = size.y;
		box[0].position = sf::Vector2f(x, y);
		box[1].position = sf::Vector2f(x + width, y);
		box[2].position = sf::Vector2f(x + width, y + height);
		box[3].position = sf::Vector2f(x, y + height);
		box[4].position = sf::Vector2f(x, y);

		for (int i = 0; i < 5; ++i)
			box[i].color = sf::Color::Red;

		window->draw(box);
	}
	if (isRenderSprite)
		window->draw(sprite);
}


void Tile::setTexture(const std::string& sourceName, const std::string& rectName) {
	TextureManager::getInstance().setTextureRect(sprite, sourceName, rectName);
}

int Tile::getType() {
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
