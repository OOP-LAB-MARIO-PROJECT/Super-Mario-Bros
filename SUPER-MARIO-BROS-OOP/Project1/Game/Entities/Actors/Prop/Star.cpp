#include "Star.h"

Star::Star(sf::Vector2f _pos, sf::Vector2f _size) : Collectable(_pos, sf::Vector2f(14, 16)) {
	isRenderHitbox = false;
	isRenderSprite = true;
	std::vector<std::vector<std::string>> runTexture = { {	"star-0",
															"star-1",
															"star-2",
															"star-3"},
														  {	"star-0",
															"star-1",
															"star-2",
															"star-3"} };
	stateCache["RUN"] = std::make_shared<RunningState>("item-object", runTexture, 0.15);
	score = 200;
	setState("RUN");
}


void Star::setState(const std::string& stateName) {
	if (stateCache.find(stateName) != stateCache.end()) {
		auto& state = stateCache[stateName];
		if (state != nullptr) {
			currentState = state;
		}
	}
	else {
		//std::cout << "Can not find State " << stateName << "\n";
	}
}

int Star::getType() {
	return RED_MUSHROOM;
}

void Star::update(float deltatime) {
	if (currentState) {
		currentState->handle(this, deltatime);
		currentState->update(this, deltatime);
	}


	if (dist < 10.f) {
		setVel({ 0, -7 });
		dist += 7 * deltatime;
		setPos(getPos() + getVel() * deltatime);
		return;
	}

	for (auto en : otherEntities) if (en->getType() == TILE) {
		Hitbox ob = en->getHitbox();
		ob.vel = sf::Vector2f{ 0.f, 0.f };
		obstacle.push_back(ob);
	}

	int dir = resolveCollideGround(obstacle, deltatime);
	setPos(getPos() + getVel() * deltatime);  //update right after collision for best resolution


	if (dir & (1 << 2)) setVel({ getVel().x, 0 });
	if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(50, getVel().y));
	if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-50, getVel().y));

	if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
		if (facing == 1)
			setVel(sf::Vector2f(50, getVel().y));
		else
			setVel(sf::Vector2f(-50, getVel().y));
	}

	// 1 << 1 = left 
	behavior(deltatime);
	performPhysics(deltatime);
}

void Star::behavior(float detatime) {
}

void Star::touched(float detatime) {
	kill();
	GameConfig::getInstance().addScore(score);
	GameConfig::getInstance().marioState = INVINCIBLE;
}

void Star::affectOther(Entity* other, float deltateim) {
	touched(deltateim);
}

