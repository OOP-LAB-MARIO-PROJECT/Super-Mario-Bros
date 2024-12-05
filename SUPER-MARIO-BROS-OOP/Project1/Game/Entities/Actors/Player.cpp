#include "Player.h"


Player::Player() {
	throw std::exception("Need to init the rigth construtor for player");
}

Player::Player(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size) {
	isRenderSprite = true;
	isRenderHitbox = true;
	facing = 1;

	std::vector<std::vector<std::string>> idleTexture = { { "left-small-mario-7" }, {"right-small-mario-6"} };
	stateCache["IDLE"] = std::make_shared<IdleState>("mario", idleTexture, 0);


	std::vector<std::vector<std::string>> runTexture = { {	"left-small-mario-13", 
															"left-small-mario-12", 
															"left-small-mario-11" }, 
														  {	"right-small-mario-0",
															"right-small-mario-1",
															"right-small-mario-2"} };
	stateCache["RUN"] = std::make_shared<RunningState>("mario", runTexture, 0);

	std::vector<std::vector<std::string>> jumpTexture = { { "left-small-mario-9" }, {"right-small-mario-4"} };
	stateCache["JUMP"] = std::make_shared<JumpingState>("mario", jumpTexture, 0);


	std::vector<std::vector<std::string>> slideTexture = { { "left-small-mario-10" }, {"right-small-mario-3"} };
	stateCache["SLIDE"] = std::make_shared<SlideState>("mario", slideTexture, 0.3f);

	std::vector<std::vector<std::string>> killTexture = { { "left-small-mario-6" }, {"right-small-mario-7"} };
	stateCache["KILL"] = std::make_shared<KillState>("mario", killTexture, 0.3f);

	std::vector<std::vector<std::string>> deadTexture = { { "left-small-mario-8" }, {"right-small-mario-5"} };
	stateCache["DEAD"] = std::make_shared<DeadState>("mario", deadTexture, 2.5f);
	setState("IDLE");
}

void Player::setState(const std::string& stateName) {
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


void Player::update(float deltatime) {


	if (deadthTimer > 2.5) GameConfig::getInstance().levelStatus = RESTART, health = 1, deadthTimer = 0, isDead = false;
	
	shootTimer -= deltatime;
	if (shootTimer < 0) shootTimer = 0;
	
	
	if (currentState) {
		//std::cout << "Current state exists" << std::endl;
		currentState->handle(this, deltatime);
		currentState->update(this, deltatime);
	}
	
	performPhysics(deltatime);
	

	if (health <= 0) {
		isDead = true;
		if (health == 0) setVel({ 0, -180.0f }), health--;
		deadthTimer += deltatime;
		setPos(getPos() + getVel() * deltatime);
		return;
	}

	sf::Vector2f vx = getVel();
	int isCollide = resolveCollideGround(obstacle, deltatime);

	if (getPos().y > 800) setVel(sf::Vector2f(getVel().x, 0));
	isOnGround = isCollide & (1 << 2);


	if (isOnGround)
		setFric({ 3, 0 }), isJumping = false;
	else
		setFric({ 0, 0 });

	


	setPos(getPos() + getVel() * deltatime);
	setSpritePos(getPos() - sf::Vector2f{ 2, 2 });

	if (isCollide & 5) // touch top or bottom
		setVel({ getVel().x, 0 }), isJumping = false;

	std::vector <Entity*> other = otherEntities;

	for (const auto& en : other) { // player interact with surrounding enemies
		int dir = dynamicRectVsRect(getHitbox(), deltatime, getVel() - en->getHitbox().vel, en->getHitbox());
		if (dir == -1) continue;
		if (en->getType() == ENEMY) {
			if (dir == TOP) setVel({ getVel().x, -20 }), en->inflictDamage(), isKilling = true;
			en->affectOther(this);
			continue;
		}
		en->touched(deltatime);
	}

	other = nearPointerTiles;
	if (other.size()) {
		float curDist = 1e9;
		Entity* cur = NULL;
		sf::Vector2f pcenter = getPos() + getSize() / 2.f;
		for (const auto& tile : other) {

			Hitbox tmp = getHitbox();

			if (isOnGround) tmp.vel.y = 1;
			int dir = dynamicRectVsRect(getHitbox(), deltatime, tmp.vel, tile->getHitbox());
			if (dir == -1) continue;
			sf::Vector2f center = tile->getHitbox().pos + tile->getHitbox().size / 2.f;			
			float dist = (pcenter.x - center.x) * (pcenter.x - center.x) + (pcenter.y - center.y) * (pcenter.y - center.y);
			if (dist < curDist) curDist = dist, cur = tile;	
		}

		if (cur) cur->affectOther(this, deltatime);
	}

}

void Player::jump(float deltatime) {
	if (isDead) return;
	if (isOnGround && !isJumping) {
		setVel({ getVel().x, -190 });
		isOnGround = false;
		reachMaxHeight = false;
		isJumping = true;
	}
	else if (isJumping) {
		if (reachMaxHeight) return;
		sf::Vector2f newVel = getVel();
		newVel += sf::Vector2f(0, -90000) * deltatime;
		if (newVel.y < -198.f)
			newVel.y = -198.f, reachMaxHeight = true;
		setVel(newVel);
	}
}

void Player::notJump(float deltatime) {
	if (!isJumping) return;
	isJumping = false;
	setVel({ getVel().x, getVel().y / 3 });
}

void Player::moveLeft(float deltatime) {
	if (isDead) return;
	if (!isOnGround) {
		if (facing == 1) setVel(getVel() + sf::Vector2f(10, 0) * deltatime);
		else setVel(getVel() + sf::Vector2f(-20, 0) * deltatime);
		return;
	}
	facing = -1;

	const float capSpeed = -140;
	const float acce = -500;
	setVel({ getVel().x + -7, getVel().y});
	if (getVel().x < capSpeed) setVel(sf::Vector2f(capSpeed, getVel().y));
}

void Player::shoot(float deltatime) {
	if (shootTimer <= 0.5) {
		EntityManager::getInstance().addEntity(new Fireball(getPos(), sf::Vector2f(4, 4), getFacing()));
		shootTimer = 1;
	}
}

void Player::moveRight(float deltatime) {
	if (isDead) return;
	if (!isOnGround) {
		if (facing == -1) setVel(getVel() + sf::Vector2f(-10, 0) * deltatime);
		else setVel(getVel() + sf::Vector2f(20, 0) * deltatime);
		return;
	}
	facing = 1;
	//setVel(sf::Vector2f(140, getVel().y));
	const float capSpeed = 140;
	const float acce = 500000000;
	setVel({ getVel().x + 7, getVel().y });
	if (getVel().x > capSpeed) setVel(sf::Vector2f(capSpeed, getVel().y));
}

int Player::getType() {
	return PLAYER;
}

void Player::inflictDamage() {
	health--;
}

void Player::setPos(sf::Vector2f pos) {
	Actor::setPos(pos);
	setSpritePos(pos - sf::Vector2f(2, 2));
}




