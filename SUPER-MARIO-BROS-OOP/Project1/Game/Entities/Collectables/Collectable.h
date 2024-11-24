#pragma once
#include "../Entity.h"
#include "../../Components/Collision.h"
#include "../../../Utils/TextureManager.h"
#include "../../../Utils/SoundManager.h"

class Collectable : public Entity, public Collision
{
private:

	sf::RectangleShape rect;
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f size;

public:
	Collectable(sf::Vector2f pos, sf::Vector2f size) : pos(pos), size(size) {
		rect.setPosition(pos);
		rect.setSize(size);
		rect.setFillColor(sf::Color::Yellow);

	};
	~Collectable() {};

	void setSpritePos(sf::Vector2f pos);
	void setTexture(const std::string& sourceName, const std::string& rectName);

	void render(sf::RenderWindow* window) const;
	virtual void update(float deltaTime) = 0;
	virtual void applyEffect() = 0;
	//sf::RectangleShape getPlayer() const {};
	bool isCollideWithPlayer(sf::Vector2f pos, sf::Vector2f size);

	Hitbox getHitbox();
};

