#include "TileFactory.h"


std::string TileFactory::findProperties(std::string& s) {
	size_t delimiterPos = s.find('#');
	if (delimiterPos == std::string::npos) {
		return "";
	}
	std::string properties = s.substr(delimiterPos + 1);
	s = s.substr(0, delimiterPos);
	return properties;
}

Tile* TileFactory::createTile(std::string type, sf::Vector2f pos, sf::Vector2f size) {

	std::string properties = findProperties(type);
	if (properties != "") std::cout << properties << '\n';

	if (TILETYPE::isInteractable(type)) {
		if (type == "question") {
			Tile* r = new QuestionTile(pos, size, properties);
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}

		if (type == "hammer") {
			Tile* r = new BossHammer(pos, size, false);
			r->setTexture("tiles", type + "-0");
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}

		if (type == "bridge") {
			Tile* r = new Brigde(pos, size, false);
			r->setTexture("tiles", type + "-0");
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}

		Tile* r = new MoveUpTile(pos, size, false);
		r->setTexture("tiles", type + "-0");
		r->setRenderSprite(true);
		r->setRenderHitbox(false);
		return r;
	}

	if (TILETYPE::isPipeHead(type)) {
		Tile* r = new PipeHead(pos, size, false, properties, type);
		return r;
	}

	if (TILETYPE::isNormalPlatform(type)) {
		Tile* r = NULL;
		if (properties == "trans")
			r = new Tile(pos, size, true);
		else
			r = new Tile(pos, size, false);
		r->setTexture("tiles", type + "-0");
		r->setRenderSprite(true);
		r->setRenderHitbox(false);
		return r;
	}

	if (type == "moving-platform") {
		return new MovingPlatform(pos, size, false, properties);
	}

	if (type == "rotate-fire") {
		Tile* r = new RotateFire(pos, size, 8);
		std::string tmp = "block4";
		r->setTexture("tiles", tmp + "-0");
		r->setRenderSprite(true);
		r->setRenderHitbox(false);
		return r;
	}

	if (TILETYPE::isTransparent(type)) {
		Tile* r = new Tile(pos, size, true);
		r->setTexture("tiles", type + "-0");
		r->setRenderSprite(true);
		r->setRenderHitbox(false);
		return r;
	}

	return new Tile(pos, size);
}