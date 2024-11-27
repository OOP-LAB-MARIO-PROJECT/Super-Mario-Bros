#pragma once
#include "../Entity.h"
#include "../Common.h"
class Tile : public Entity {
private:
	sf::RectangleShape hitbox;
	sf::Sprite sprite;

	sf::Vector2f pos;
	sf::Vector2f size;

	ENTITY_TYPE currentType = ENTITY_TYPE::TILE;

	bool isTransparent = true;
public:

	Tile(sf::Vector2f _pos, sf::Vector2f _size, bool isTrans = true);
	~Tile() {};
	void render(sf::RenderWindow* window) const override;
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
	ENTITY_TYPE getType() override;
	void touched(float deltatime) override {};
};

