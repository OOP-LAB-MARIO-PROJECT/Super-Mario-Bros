#include "Flag.h"


Poll::Poll(sf::Vector2f pos, sf::Vector2f size, bool isTrans) : Tile(pos, size, false) {

	auto savePos = pos;
	auto savePos2 = pos;
	savePos.x -= size.x / 2.f;
	savePos.y += 1;

	pos.x += size.x / 2.f - 1;
	size.x = 2;
	setPos(pos);
	setSpritePos(savePos2);

	this->size = size;

	isRenderSprite = true;
	isRenderHitbox = true;

	setTexture("tiles", "flag-body-1-0");


}

void Poll::affectOther(Entity* other, float deltatime) {
	if (other->getType() != PLAYER || _touched) return;
	other->messageFromOther = "FlagTouched";
	_touched = true;
}

void Poll::touched(float deltatime) {
	_touched = true;
}

bool Poll::isTouch() { return _touched; }

Flag::Flag(sf::Vector2f pos) : Tile(pos, sf::Vector2f(16, 16), true) {

	isRenderSprite = true;
	setTexture("item-object", "flag-0");
}

void Flag::update(float deltatime) {
	if (!isGodown || isEnd) return;
	setPos(getPos() + sf::Vector2f(0, 60) * deltatime);
	setSpritePos(getPos());
	if (getPos().y > GameConfig::getInstance().cameraBase - 16)
		isEnd = true;
}

FullFlag::FullFlag(sf::Vector2f pos) : Tile(pos, sf::Vector2f(16, 16), false) {
	for (int i = 0; i < 9; i++) {
		pos.y -= 16;
		Poll* p = new Poll(pos, sf::Vector2f(16, 16), false);
		poll.push_back(p);
		EntityManager::getInstance().addEntity(p);
	}

	pos.x -= 8;
	flag = new Flag(pos);
	EntityManager::getInstance().addEntity(flag);
	isRenderSprite = true;
	setTexture("tiles", "block4-0");
}

void FullFlag::update(float deltatime) {
	int pointGet = 100;
	if (isPollTouch) return;
	if (!isPollTouch) 
		for (auto p : poll) {
			if (p->isTouch())
				isPollTouch = true;
			pointGet += pointGet / 2;
		}

	if (!isPollTouch) return;
	for (auto p : poll) p->touched(deltatime);
	flag->isGodown = true;
	GameConfig::getInstance().addScore(pointGet);
}

