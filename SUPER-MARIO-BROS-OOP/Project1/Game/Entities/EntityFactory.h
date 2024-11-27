#pragma once
#include "EntityList.h"
#include <string>
#include <vector>

namespace FACTORY_ENTITY_TYPE {

	static std::vector <std::string> enemies = {
		"goompa",
		"troopa-koopa"
	};

	static std::vector <std::string> collectable = {
		"red-mushroom",
		"green-mushroom",
		"brown-mushroom",
		"coin"
	};

	static bool isEnemy(const std::string& type) {
		return std::find(enemies.begin(), enemies.end(), type) != enemies.end();
	}

	static bool isCollectable(const std::string& type) {
		return std::find(collectable.begin(), collectable.end(), type) != collectable.end();
	}

	static bool isEntityNotTile(const std::string& type) {
		return isEnemy(type) || isCollectable(type);
	}

};

class EntityFactory {
public:
	Entity* createEntity(const std::string& type, sf::Vector2f pos, sf::Vector2f size);
};
