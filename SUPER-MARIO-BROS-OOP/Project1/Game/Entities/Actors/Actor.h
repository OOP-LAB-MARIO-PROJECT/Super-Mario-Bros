#pragma once
#include "SFML/Graphics.hpp"
#include "../Entity.h"
#include "../../Components/Collision.h"
#include "../../Components/Physics.h"

class Actor : public Entity, public Collision, public Physics {
private:
	sf::Sprite sprite;
	sf::RectangleShape rect; // for rendering
	sf::Vector2f pos;
	sf::Vector2f size;
	// spritesheet
protected:
	bool isOnGround = false;
	bool autoSpriteFollowHitbox = true;
	int facing = 0;

public:

	Actor(sf::Vector2f _pos, sf::Vector2f _size);
	Actor() {};

	
	void render(sf::RenderWindow* window) const override;
	
	sf::Vector2f getPos() const;
	void setPos(sf::Vector2f pos);

	sf::Vector2f getSize() const;
	void setSize(sf::Vector2f size);
	
	
	void setSpritePos(sf::Vector2f pos);
	void setTexture(const std::string& sourceName, const std::string& rectName);
	
	int resolveCollideGround(std::vector <Hitbox> vi, float deltaTime);

	Hitbox getHitbox();
	ENTITY_TYPE getType() override;

};

