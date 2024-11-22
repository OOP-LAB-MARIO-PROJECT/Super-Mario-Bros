#include "Actor.h"

void Actor::render(sf::RenderWindow* window) const {
	//std::cout << "Rendering player!" << std::endl;

	if (isRenderHitbox)
		window->draw(rect);
	if (isRenderSprite)
		window->draw(sprite);
}

Actor::Actor(sf::Vector2f _pos, sf::Vector2f _size) :
	pos(_pos), size(_size), Physics({ 0, 0 }, { 0, 260 })
{
	rect.setFillColor(sf::Color::Green);
	rect.setPosition(pos);
	rect.setSize(size);
	sprite.setPosition(pos);

	std::cout << "made the player green\n";
};


void Actor::setPos(sf::Vector2f _pos) {
	pos = _pos;
	rect.setPosition(pos);
	if (autoSpriteFollowHitbox) sprite.setPosition(pos);
}

void Actor::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}


void Actor::setSize(sf::Vector2f _size) {
	size = _size;
	rect.setScale(size);
}

sf::Vector2f Actor::getPos() const {
	return pos;
}

sf::Vector2f Actor::getSize() const {
	return size;
}

sf::RectangleShape& Actor::getHitbox() {
	return rect;
}

int Actor::resolveCollideGround(std::vector <sf::RectangleShape> vi, float deltaTime) {
	sf::Vector2f pos = getPos();
	sf::Vector2f vel = getVel();
	int dir = 0;
	sf::Vector2f expected = rectVsTerain(rect, vi, getVel(), deltaTime, pos, dir);
	if (expected == getVel()) return 0;
	setVel(expected);
	return dir;
}

void Actor::setTexture(const std::string& sourceName, const std::string& rectName) {
	TextureManager::getInstance().setTextureRect(sprite, sourceName, rectName);
}
