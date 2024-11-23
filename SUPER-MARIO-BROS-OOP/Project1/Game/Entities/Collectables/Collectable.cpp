#include "Collectable.h"

void Collectable::render(sf::RenderWindow* window) const {
	if (isRenderHitbox)
		window->draw(rect);
	if (isRenderSprite)
		window->draw(rect);
}

void Collectable::update(float deltaTime) {}

bool Collectable::isCollideWithPlayer(sf::Vector2f pos, sf::Vector2f size) {
	return rectVsRect({ pos, size }, { this->pos, this->size });
}

void Collectable::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Collectable::setTexture(const std::string& sourceName, const std::string& rectName) {
	TextureManager::getInstance().setTextureRect(sprite, sourceName, rectName);
}

