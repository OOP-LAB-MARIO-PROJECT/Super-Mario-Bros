#include "Actor.h"

void Actor::render(sf::RenderWindow* window) const {
	//std::cout << "Rendering player!" << std::endl;

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

Actor::Actor() {};

Actor::Actor(sf::Vector2f _pos, sf::Vector2f _size) :
	pos(_pos), size(_size), Physics({ 0, 0 }, { 0, 260 })
{
	sprite.setPosition(pos);

	std::cout << "made the player green\n";
};


void Actor::setPos(sf::Vector2f _pos) {
	pos = _pos;
	if (autoSpriteFollowHitbox) sprite.setPosition(pos);
}

void Actor::setSpritePos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}


void Actor::setSize(sf::Vector2f _size) {
	size = _size;

}

void Actor::setVel(sf::Vector2f vel) {
	hitbox.vel = vel;
	Physics::setVel(vel);
}

sf::Vector2f Actor::getVel() const {
	return Physics::getVel();
}

sf::Vector2f Actor::getPos() const {
	return pos;
}

sf::Vector2f Actor::getSize() const {
	return size;
}

Hitbox Actor::getHitbox() {
	return {pos, size, getVel()};
}

int Actor::getFacing() {
	return facing;
}

bool Actor::getIsOnGround() {
	return isOnGround;
}

bool Actor::getIsKilling() const {
	return isKilling;
}

void Actor::setIsKilling(bool a) {
	isKilling = a;
}

bool Actor::getIsDead() const {
	return isDead;
}

void Actor::setIsDead(bool a) {
	isDead = a;
}

int Actor::resolveCollideGround(std::vector <Hitbox> vi, float deltaTime) {
	sf::Vector2f pos = getPos();
	sf::Vector2f vel = getVel();
	int dir = 0;
	sf::Vector2f expected = rectVsTerain(getHitbox(), vi, getVel(), deltaTime, pos, dir);
	if (expected == getVel()) return 0;
	Physics::setVel(expected);
	return dir;
}

void Actor::setTexture(const std::string& sourceName, const std::string& rectName) {
	TextureManager::getInstance().setTextureRect(sprite, sourceName, rectName);
}

int Actor::getType() {
	return ACTOR;
}

void Actor::setSpriteScale(float x, float y) {
	sprite.setScale(x, y);
}
void Actor::setSpriteOrigin(sf::Vector2f ori) {
	sprite.setOrigin(ori);
}
