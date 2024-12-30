#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utils/TextureManager.h"
#include "../../Utils/SceneManager.h"
#include "../../Utils/SoundManager.h"
#include "../../Utils/Observer.h"
#include "../GameConfig.h"

enum ENTITY_TYPE {
	PROJECTILE,
	ENEMY,
	TILE,
	MOVING_TILE,
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
	COIN,
	DOOR,
	TRANS
};

struct Hitbox {
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f vel;
};

class Entity: public Observer<Entity>
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
	bool needUpdateEnvironment = true;
	std::string messageFromOther = "";

	void kill() { _isDead = true; };
	bool isDead() const { return _isDead; }
	virtual ~Entity() = default;


	virtual void setPos(sf::Vector2f pos);
	virtual void setSize(sf::Vector2f size);
	virtual void setVel(sf::Vector2f vel);
	virtual void updatePositionAndPhysic(float deltaTime) {}

	void setRenderHitbox(bool f);
	void setRenderSprite(bool f);
	virtual void updateEvironment(const std::vector <Hitbox>& obstacle, const std::vector <Entity*>& otherEntities);

	virtual void render(sf::RenderWindow* window) const = 0;
	virtual void update(float deltaTime) = 0;
	virtual void inflictDamage() {};
	virtual void touched(float deltatime) {};

	// FUNCTION TO NOTE
	virtual int getType() = 0; // get the type of entities -> use for distinguish between entyties and use for conditional behavior of entities 
	virtual Hitbox getHitbox() = 0; // get the dynamic hitbox of an object -> make it easier for detection collision
	virtual void affectOther(Entity* other);
	virtual void affectOther(Entity* other, float deltatime);
	virtual bool getIsDeadByOtherThings() { return false; }
	virtual void setIsDeadByOtherThings(bool a) { }
};

