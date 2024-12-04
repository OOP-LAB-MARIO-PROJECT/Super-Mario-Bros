#include "EntityFactory.h"


Entity* EntityFactory::createEntity(std::string type, sf::Vector2f pos, sf::Vector2f size) {

	std::string properties = findProperties(type);

	if (type == "goompa")
		return new Goompa(pos, size);

	if (type == "troopa-koopa") {
	//return new TroopaKoopa(pos, size, map);
	}

	if (type == "red-mushroom") {
		return new RedMushroom(pos, size);
	}

	if (type == "coin") {
		return new Coin(pos, size);
	}

	if (type == "castle-door") {
		return new CastleGate(pos, size, properties);
	}


	//return new Goompa(pos, size, map);
	return NULL;
}