#include "EntityFactory.h"


Entity* EntityFactory::createEntity(std::string type, sf::Vector2f pos, sf::Vector2f size) {

	std::string properties = findProperties(type);
	
	if (type == "background")
		return NULL;

	if (type == "goompa")
		return new Goompa(pos, size);

	if (type == "troopa-koopa") {
		return new KoopaTroopa(pos, size);
	}

	if (type == "piranha-plant") {
		return new PiranhaPlant(pos, size);
	}

	if (type == "red-mushroom") {
		return new RedMushroom(pos, size);
	}

	if (type == "coin") {
		if (properties == "instant")
			return new Coin(pos, size, true);
		return new Coin(pos, size);
	}

	if (type == "castle-door") {
		return new CastleGate(pos, size, properties);
	}

	if (type == "king-koopa") {
		return new KingKoopa(pos, size);
	}
	
	if (type == "star") {
		return new Star(pos, size);
	}

	if (type == "flower") {
		return new Flower(pos, size);
	}


	//return new Goompa(pos, size, map);
	return NULL;
}