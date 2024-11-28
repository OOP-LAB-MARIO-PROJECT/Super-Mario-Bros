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
}

void Coin::behavior(float deltatime) {

}

void Coin::touched(float deltatime) {
	kill();
	GameConfig::getInstance().addCoin();
	GameConfig::getInstance().addScore(score);
	SoundManager::getInstance().playSound("collect", false);
}

ENTITY_TYPE Coin::getType() {
	return COIN;
}