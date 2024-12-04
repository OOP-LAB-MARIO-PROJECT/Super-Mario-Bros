# HOW TO USE ENTITY.H

`Entity,h`

```c++

#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utils/TextureManager.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/SoundManager.h"
#include "../GameConfig.h"

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
	PIPE_HEAD,
	COIN
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
	// API being update in entities
	Hitbox hitbox;
	std::vector <Hitbox> obstacle;
	std::vector <Entity*> otherEntities;
	int isRenderHitbox = true;
	int isRenderSprite = false;

	void kill() { _isDead = true; };
	bool isDead() const { return _isDead; }
	virtual ~Entity() = default;


	virtual void setPos(sf::Vector2f pos); // set position of the hitbox
	virtual void setSize(sf::Vector2f size); // set size of the hitbox
	virtual void setVel(sf::Vector2f vel); // set velocity of the hitbox

	void setRenderHitbox(bool f);
	void setRenderSprite(bool f);
	void updateEvironment(const std::vector <Hitbox>& obstacle, const std::vector <Entity*>& otherEntities);

	virtual void render(sf::RenderWindow* window) const = 0;
	virtual void update(float deltaTime) = 0;
	virtual void inflictDamage() {}; // specify behavior of entities when it is being touched
	virtual void touched(float deltatime) {}; // specify behavior of entities when it is being touched

	// FUNCTION TO NOTE
	virtual ENTITY_TYPE getType() = 0; // get the type of entities -> use for distinguish between entyties and use for conditional behavior of entities
	virtual Hitbox getHitbox() = 0; // get the dynamic hitbox of an object -> make it easier for detection collision
	virtual void affectOther(Entity* other); // When this entity is touching and there is an affect to other entities -> use for conditional behavior of entities
};


```

# 1. Enemy being inherited from Entity.h, and there are some api implemented in Enemy.h
# 2. how to use Enemy.h
