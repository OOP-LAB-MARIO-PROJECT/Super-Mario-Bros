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
	ACTOR,
	RED_MUSHROOM,
	GREEN_MUSHROOM,
	BROWN_MUSHROOM,
	PIPE_HEAD_TELE,
	PIPE_HEAD
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
	std::vector <Hitbox> obstacle;
	std::vector <Entity*> otherEntities;
	int isRenderHitbox = true;
	int isRenderSprite = false;

	void kill() { _isDead = true; };
	bool isDead() const { return _isDead; }
	virtual ~Entity() = default;


	virtual void setPos(sf::Vector2f pos);
	virtual void setSize(sf::Vector2f size);
	virtual void setVel(sf::Vector2f vel);

	void setRenderHitbox(bool f);
	void setRenderSprite(bool f);
	void updateEvironment(const std::vector <Hitbox>& obstacle, const std::vector <Entity*>& otherEntities);

	virtual void render(sf::RenderWindow* window) const = 0;
	virtual void update(float deltaTime) = 0;
	virtual void inflictDamage() {};
	virtual void touched(float deltatime) {};

	// FUNCTION TO NOTE
	virtual ENTITY_TYPE getType() = 0; // get the type of entities -> use for distinguish between entyties and use for conditional behavior of entities 
	virtual Hitbox getHitbox() = 0; // get the dynamic hitbox of an object -> make it easier for detection collision
	virtual void affectOther(Entity* other);
};

