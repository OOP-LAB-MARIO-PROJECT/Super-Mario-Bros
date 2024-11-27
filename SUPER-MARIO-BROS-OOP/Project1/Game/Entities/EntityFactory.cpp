#include "EntityFactory.h"
Entity* EntityFactory::createEntity(const std::string& type, sf::Vector2f pos, sf::Vector2f size, Map* map) {
	 if (type == "goompa") {
		 //return new Enemy(pos, size, map);
		 return new Goompa(pos, size, map);
	 }
	 //return new Goompa(pos, size, map);
	 return NULL;
}