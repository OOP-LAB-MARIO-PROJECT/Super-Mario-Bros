#include "Brigde.h"

Brigde::Brigde(sf::Vector2f pos, sf::Vector2f size, bool isTrans) : Tile(pos, size, false) {

}
int Brigde::getType() {
	return TILE;
}

void Brigde::update(float deltatime) {
	if (GameConfig::getInstance().isWinning == false) return;
	if (!isFirstUpdate) {
		timer = abs(GameConfig::getInstance().winingPos.x - getPos().x);
		isFirstUpdate = true;
	}

	timer -= deltatime * 80;
	if (timer < 0) kill();
}