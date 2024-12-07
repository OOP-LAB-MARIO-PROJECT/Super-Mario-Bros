#pragma once
#include "EntityList.h"
#include <string>
#include <vector>

static std::string findProperties(std::string& s)  {
	size_t delimiterPos = s.find('#');
	if (delimiterPos == std::string::npos) {
		return "";
	}
	std::string properties = s.substr(delimiterPos + 1);
	s = s.substr(0, delimiterPos);
	return properties;
}
namespace FACTORY_ENTITY_TYPE {

	static std::vector <std::string> enemies = {
		"goompa",
		"troopa-koopa",
		"piranha-plant",
		"king-koopa"
	};

	static std::vector <std::string> collectable = {
		"red-mushroom",
		"green-mushroom",
		"brown-mushroom",
		"coin",
		"castle-door"
	};

	static bool isEnemy(const std::string& type) {
		return std::find(enemies.begin(), enemies.end(), type) != enemies.end();
	}

	static bool isCollectable(const std::string& type) {
		return std::find(collectable.begin(), collectable.end(), type) != collectable.end();
	}

	static bool isEntityNotTile(const std::string& type) {
		std::string tmp = type;
		findProperties(tmp);
		return isEnemy(tmp) || isCollectable(tmp);
	}

};


class EntityFactory {
public:
	Entity* createEntity(std::string type, sf::Vector2f pos, sf::Vector2f size);
};
