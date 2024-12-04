#include "Coin.h"


Coin::Coin(sf::Vector2f(pos), sf::Vector2f(size)) : Collectable(pos, size) {
	setSize({ 10, getSize().y });
	isRenderSprite = true;
	isRenderHitbox = false;
	score = 200;
	aniloop = 0;
	timer = 0;

	animation = {
		"coin-0",
		"coin-1",
		"coin-2",
		"coin-3"
	};
	setTexture("item-object", "coin-0");
}

void Coin::update(float deltatime) {
	timer += deltatime;
	if (timer > 0.1) {
		(++aniloop) %= animation.size();
		setTexture("item-object", animation[aniloop]);
		timer = 0;
	}
	
	if (isTouch) {
		performPhysics(deltatime);
		setPos(getPos() + getVel() * deltatime);
		fallingTimer -= deltatime;
		touched(deltatime);
		return;
	}
	//std::cout << obstacle.size() << '\n';

	for (auto& o : obstacle) {
		Collision::rect dr = { o.pos, o.size, o.vel };
		if (rectVsRect(dr, { getPos(), getSize() })) {
			setVel(sf::Vector2f{ 0, -90 });
			fallingTimer = 1;
			touched(deltatime);
			return;
		}
	}

}

void Coin::behavior(float deltatime) {

}

void Coin::touched(float deltatime) {
	if (fallingTimer <= 0) kill();
	if (isTouch) return;
	GameConfig::getInstance().addCoin();
	GameConfig::getInstance().addScore(score);
	SoundManager::getInstance().playSound("collect", false);
	isTouch = true;
}

int Coin::getType() {
	return COIN;
}