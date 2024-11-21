#pragma once
#include <SFML/Graphics.hpp>
#include "../../Utils/TextureManager.h"
#include "../../Utils/SceneManager.h"

class Entity
{
	bool _isDead = false;
	// id
	int id = -1;

public:
	int isRenderHitbox = true;
	int isRenderSprite = false;

	void kill() { _isDead = true; };
	bool isDead() const { return _isDead; }
	virtual ~Entity() = default;

	void setRenderHitbox(bool f) { isRenderHitbox = f; }
	void setRenderSprite(bool f) { isRenderSprite = f; }

	virtual void render(sf::RenderWindow* window) const = 0;
	virtual void update(float deltaTime) = 0;
};

