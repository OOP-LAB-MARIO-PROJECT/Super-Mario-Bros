#include "BossHammer.h"


BossHammer::BossHammer(sf::Vector2f pos, sf::Vector2f size, bool isTrans) : Tile(pos, size, false) {
}

int BossHammer::getType() {
	return TILE;
}

void BossHammer::affectOther(Entity* other, float deltatime) {
	if (other->getType() != PLAYER) return;
	GameConfig::getInstance().isWinning = true;
	GameConfig::getInstance().winingPos = getPos();
}

void BossHammer::update(float deltatime) {

}