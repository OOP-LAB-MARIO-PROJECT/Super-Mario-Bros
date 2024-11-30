#include "CastleGate.h"

CastleGate::CastleGate(sf::Vector2f pos, sf::Vector2f size, std::string nextLevel) : Collectable(pos, size) {
	nxt = nextLevel;
	isRenderHitbox = false;
	isRenderSprite = true;
	std::cout << "set next level to be: " + nextLevel << '\n';
	setTexture("tiles", "castle-door-0");
}


ENTITY_TYPE CastleGate::getType() {
	return DOOR;
}

void CastleGate::touched(float deltatime) {
	std::cout << nxt << '\n';
	GameConfig::getInstance().levelStatus = NEXT_LEVEL;
	GameConfig::getInstance().setCurrentLevel(nxt);
}