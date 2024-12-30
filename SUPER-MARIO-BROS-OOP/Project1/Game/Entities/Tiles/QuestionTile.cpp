#include "QuestionTile.h"


QuestionTile::QuestionTile(sf::Vector2f _pos, sf::Vector2f _size, std::string power) : MoveUpTile(_pos, _size, false), prop(power) {
	if (prop.empty()) prop = "coin";
	isRenderSprite = true;
	isEmpty = false;
	setTexture("item-object", "question-block-0");
	animation = {
		"question-block-0",
		"question-block-1",
		"question-block-2",
		"question-block-3"
	};
}

void QuestionTile::touched(float deltatime) {
	if (isTouch || isEmpty) return;
	isTouch = true;
	setVel({ 0, -90 });
}


void QuestionTile::update(float deltatime) {
	if (!isTouch && isEmpty) return;
	if (isTouch) setPos(getPos() + getVel() * deltatime);

	if (isTouch) {
		if (!isEmpty) {
			EntityFactory factory;
			sf::Vector2f _pos = getPos() - sf::Vector2f(0, 5);
			sf::Vector2f _size = { 16.f, 16.f };

			if (prop == "coin") {
				EntityManager::getInstance().addEntity(
					factory.createEntity("coin#instant", _pos, _size)
				);
			}

			if (prop == "power") {
				MARIO_STATE mst = GameConfig::getInstance().marioState;

				if (mst == SMALL)
					EntityManager::getInstance().addEntity(
						factory.createEntity("red-mushroom", _pos, _size)
					);
				
				if (mst == BIG)
					EntityManager::getInstance().addEntity(
						factory.createEntity("flower", _pos, _size)
					);

				if (mst == WHITE_BIG)
					EntityManager::getInstance().addEntity(
						factory.createEntity("coin#instant", _pos, _size)
					);
			} 

			if (prop == "star") {
				EntityManager::getInstance().addEntity(
					factory.createEntity("star", _pos, _size)
				);
			}
		
		}

		isEmpty = true;
		setTexture("tiles", "block4-0");
	}

	if (getPos().y > initpos.y) {
		isTouch = false;
		setVel(sf::Vector2f{ 0, 0 });
		setPos(initpos);
	}

	if (isTouch) performPhysics(deltatime);
	if (!isEmpty) setTexture("item-object", animation[frame]);
	aniloop++;
	if (aniloop > 15) (++frame) %= 4, aniloop = 0;
}
