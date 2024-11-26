#pragma once
#include "EntityList.h"
#include "Entity.h"
#include <string>
#include <vector>

namespace FACTORY_ENTITY_TYPE {

	static std::vector <std::string> enemies = {
		"goompa"
	};

	static bool isEnemy(const std::string& type) {
		return std::find(enemies.begin(), enemies.end(), type) != enemies.end();
	}

	static bool isEntityNotTile(const std::string& type) {
		return isEnemy(type);
	}

};

class EntityFactory {
public:
	Entity* createEntity(const std::string& type, sf::Vector2f pos, sf::Vector2f size, Map* map);
};
