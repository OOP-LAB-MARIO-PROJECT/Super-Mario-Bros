#include "CastleGate.h"

CastleGate::CastleGate(sf::Vector2f pos, sf::Vector2f size, std::string nextLevel) : Collectable(pos, size) {
	nxt = nextLevel;
	isRenderHitbox = false;
	isRenderSprite = true;
	std::cout << "set next level to be: " + nextLevel << '\n';
	setTexture("tiles", "castle-door-0");
}


int CastleGate::getType() {
	return DOOR;
}

void CastleGate::touched(float deltatime) {
	std::cout << nxt << '\n';
	if (nxt.empty()) return;
	GameConfig::getInstance().levelStatus = NEXT_LEVEL;
	GameConfig::getInstance().setNextLevel(nxt);
}

void CastleGate::affectOther(Entity* other, float deltatime) {
	touched(deltatime);
}
