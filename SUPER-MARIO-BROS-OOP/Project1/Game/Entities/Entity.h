#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utils/TextureManager.h"
#include "../../Utils/SceneManager.h"

enum ENTITY_TYPE {
	PROJECTILE,
	ENEMY,
	TILE,
	PLAYER,
	HARM_TO_ENEMY,
	HARM_TO_ALL,
	HARM_TO_PLAYER,
	PROP,
	ACTOR
};

struct Hitbox {
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f vel;
};

class Entity
{
	bool _isDead = false;
	// id
	int id = -1;
public:

	Hitbox hitbox;
	int isRenderHitbox = true;
	int isRenderSprite = false;

	void kill() { _isDead = true; };
	bool isDead() const { return _isDead; }
	virtual ~Entity() = default;

	void setRenderHitbox(bool f) { isRenderHitbox = f; }
	void setRenderSprite(bool f) { isRenderSprite = f; }

	virtual void render(sf::RenderWindow* window) const = 0;
	virtual void update(float deltaTime) = 0;
	virtual void inflictDamage() {};
	virtual void touched(float deltatime) {};

	// FUNCTION TO NOTE
	virtual ENTITY_TYPE getType() = 0; // get the type of entities -> use for distinguish between entyties and use for conditional behavior of entities 
	virtual Hitbox getHitbox() = 0; // get the dynamic hitbox of an object -> make it easier for detection collision

};

