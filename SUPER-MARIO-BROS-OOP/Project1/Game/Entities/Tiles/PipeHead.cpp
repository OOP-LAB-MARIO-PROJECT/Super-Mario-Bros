#include "PipeHead.h"
PipeHead::PipeHead(sf::Vector2f pos, sf::Vector2f size, bool isTrans, std::string properties, std::string type) : Tile(pos, size, false) {
	
	setTexture("tiles", type + "-0");
	setRenderHitbox(false);
	setRenderSprite(true);

	isUp = !(type == "pipe-side-head-bottom" || type == "pipe-side-head-up");
	if (properties == "") return;
	isTele = true;

	int p[3] = { 0, 0 };
	int i = 0;
	for (auto ch : properties) {
		if (ch == ';') {
			i++;
			continue;
		}
		p[i] = p[i] * 10 + ch - '0';
	}

	x = p[0], y = p[1];
	cameraBase = p[2];
	
}

ENTITY_TYPE PipeHead::getType() {
	if (isTele) return PIPE_HEAD_TELE;
	return PIPE_HEAD;
}

void PipeHead::affectOther(Entity* other) {
	if (
		(isUp && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) || 
		(!isUp && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	)
		if (isTele && other->getType() == PLAYER) {
			other->setPos(sf::Vector2f(x, y));
			GameConfig::getInstance().cameraBase = cameraBase;
		}
}
