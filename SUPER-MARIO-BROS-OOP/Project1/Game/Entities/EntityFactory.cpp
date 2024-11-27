#include "EntityFactory.h"

Entity* EntityFactory::createEntity(const std::string& type, sf::Vector2f pos, sf::Vector2f size) {
	 if (type == "goompa") {
		 //return new Enemy(pos, size, map);
		return new Goompa(pos, size);
	 }

	 if (type == "troopa-koopa") {
		//return new TroopaKoopa(pos, size, map);
	 }

	 if (type == "red-mushroom") {
		 return new RedMushroom(pos, size);
	 }


	 //return new Goompa(pos, size, map);
	 return NULL;
}