#pragma once
#include "../Entity.h"
#include "../../Components/Collision.h"


class Tile : public Entity, public Collision {
protected:
	sf::Sprite sprite;
	sf::Vector2f pos;
	sf::Vector2f size;

	int currentType = ENTITY_TYPE::TILE;

	bool isTransparent = true;
public:

	Tile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans = true);
	~Tile() {};
	void render(sf::RenderWindow* window) const override;
	virtual void renderExtra(sf::RenderWindow* window) const {}
	virtual void update(float deltaTime) {};
	virtual void destroy(float deltaTime) {};
	// set hitbox position, not sprite position 
	// -> refer to setPritePos(sf::Vector2f pos) for setting sprite's pos
	void setPosition(sf::Vector2f pos);
	
	sf::Vector2f getPos() const;
	// set srite and hitbox pos
	void setPos(sf::Vector2f pos);
	
	// set sprite position
	void setSpritePos(sf::Vector2f pos);

	void setTexture(const std::string& sourceName, const std::string& rectName);
	bool isTrans() { return isTransparent; }

	Hitbox getHitbox();
	int getType() override;
	void touched(float deltatime) override {};
};

