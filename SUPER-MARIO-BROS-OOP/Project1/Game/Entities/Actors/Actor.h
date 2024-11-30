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
	bool isKilling = false;
	bool isDead = false;
public:

	Actor(sf::Vector2f _pos, sf::Vector2f _size);
	Actor();

	void render(sf::RenderWindow* window) const override;
	
	sf::Vector2f getPos() const;
	void setPos(sf::Vector2f pos) override;

	sf::Vector2f getSize() const;
	void setSize(sf::Vector2f size) override;
	
	sf::Vector2f getVel() const;
	void setVel(sf::Vector2f vel) override;

	bool getIsKilling() const;
	void setIsKilling(bool a);


	bool getIsDead() const;
	void setIsDead(bool a);


	void setSpritePos(sf::Vector2f pos);
	void setTexture(const std::string& sourceName, const std::string& rectName);
	void setSpriteScale(float x, float y);
	void setSpriteOrigin(sf::Vector2f ori);
	int resolveCollideGround(std::vector <Hitbox> vi, float deltaTime);
	int getFacing();
	bool getIsOnGround();
	Hitbox getHitbox();
	virtual ENTITY_TYPE getType() override;
	virtual void update(float deltatime) override = 0;
	virtual void setState(const std::string& stateName) { }
};

