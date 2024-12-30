#include "PipeHead.h"
PipeHead::PipeHead(sf::Vector2f pos, sf::Vector2f size, bool isTrans, std::string properties, std::string type) : Tile(pos, size, false) {
	
	setTexture("tiles", type + "-0");
	setRenderHitbox(false);
	setRenderSprite(true);
	player = NULL;
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

		if (i == 3) {
			backgroundColor += ch;
			continue;
		}
		p[i] = p[i] * 10 + ch - '0';
	}

	x = p[0], y = p[1];
	cameraBase = p[2];
	std::cout << cameraBase << ' ' << backgroundColor << '\n';
}

int PipeHead::getType() {
	if (isTele) return PIPE_HEAD_TELE;
	return PIPE_HEAD;
}

void PipeHead::update(float deltatime) {
	if (player == NULL || !isTele) return;
	int dir = dynamicRectVsRect(player->getHitbox(), deltatime, player->getHitbox().vel, getHitbox());

	if (dir != TOP && dir != LEFT) return;

	if ((isUp && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ||
		(!isUp && sf::Keyboard::isKeyPressed(sf::Keyboard::D))) {
		player->setPos(sf::Vector2f(x, y));
		GameConfig::getInstance().cameraBase = cameraBase;
		if (backgroundColor == "blue") GameConfig::getInstance().backgroundColor = BLUE;
		if (backgroundColor == "black") GameConfig::getInstance().backgroundColor = BLACK;
	}
}


void PipeHead::affectOther(Entity* other, float deltatime) {
	if (other->getType() != PLAYER) return;
	player = other;
}
