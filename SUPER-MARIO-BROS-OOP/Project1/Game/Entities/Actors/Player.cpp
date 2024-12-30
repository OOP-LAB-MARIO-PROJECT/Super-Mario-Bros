#include "Player.h"


Player::Player() {
	throw std::exception("Need to init the rigth construtor for player");
}

Player::Player(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size) {
	isRenderSprite = true;
	isRenderHitbox = true;
	isTransforming = false;
	facing = 1;


	std::vector<std::vector<std::string>> idleTexture = { { "left-mario-9" }, {"right-mario-6"} };
	stateCache["IDLE"] = std::make_shared<IdleState>("mario", idleTexture, 0);


	std::vector<std::vector<std::string>> runTexture = { {	"left-mario-13",
															"left-mario-14",
															"left-mario-15" },
														  {	"right-mario-2",
															"right-mario-1",
															"right-mario-0"} };



	stateCache["RUN"] = std::make_shared<RunningState>("mario", runTexture, 0.15);

	std::vector<std::vector<std::string>> jumpTexture = { { "left-mario-11" }, {"right-mario-4"} };
	stateCache["JUMP"] = std::make_shared<JumpingState>("mario", jumpTexture, 0);


	std::vector<std::vector<std::string>> slideTexture = { { "left-mario-12" }, {"right-mario-3"} };
	stateCache["SLIDE"] = std::make_shared<SlideState>("mario", slideTexture, 0.3f);

	std::vector<std::vector<std::string>> killTexture = { { "left-mario-8" }, {"right-mario-7"} };
	stateCache["KILL"] = std::make_shared<KillState>("mario", killTexture, 0.3f);

	std::vector<std::vector<std::string>> deadTexture = { { "left-mario-10" }, {"right-mario-5"} };
	stateCache["DEAD"] = std::make_shared<DeadState>("mario", deadTexture, 2.5f);

	std::vector<std::vector<std::string>> transformTexture = { { "left-mario-3", "left-mario-2" }, {"right-mario-14", "right-mario-15"} };
	stateCache["TRANSFORMING"] = std::make_shared<TransformState>("big-mario", transformTexture, 1.2f);

	std::vector<std::vector<std::string>> dodgeTexture = { { "left-mario-10" }, {"right-mario-5"} };
	stateCache["DODGE"] = std::make_shared<DodgingState>("big-mario", dodgeTexture, 0);

	currentMode = SMALL;
	setState("IDLE");
}

void Player::setState(const std::string& stateName) {
	if (stateCache.find(stateName) != stateCache.end()) {
		auto& state = stateCache[stateName];
		if (state != nullptr) {

			if (currentMode == SMALL && !getIsTransforming()) state->setEntityName("mario");
			if (currentMode == BIG) state->setEntityName("big-mario");
			if (currentMode == WHITE_BIG) state->setEntityName("wb-mario");
			currentState = state;
		}
	}
	else {
		//std::cout << "Can not find State " << stateName << "\n";
	}
}


void Player::update(float deltatime) {

	if (getPos().y > GameConfig::getInstance().cameraBase + 64) inflictDamage();

	isInvincible = GameConfig::getInstance().isInvincible;
	if (isTransforming) isInvincible = true;

	if (isInvincible) {
		
		if (!isTransforming)
			invicibleDuration += deltatime;
		if (invicibleDuration > 5.f) {
			invicibleDuration = 0;
			GameConfig::getInstance().isInvincible = false;
		}			
	}

	if (currentMode == SMALL && GameConfig::getInstance().marioState == MARIO_STATE::BIG) {
		setIsTransforming(true);
		currentMode = BIG;
	}

	if (currentMode == BIG && GameConfig::getInstance().marioState == MARIO_STATE::WHITE_BIG) {
		currentMode = WHITE_BIG;
	}

	if (currentMode == BIG && GameConfig::getInstance().marioState == MARIO_STATE::SMALL) {
		setIsTransforming(true);
		currentMode = SMALL;
	}

	if (currentMode == SMALL && GameConfig::getInstance().marioState == MARIO_STATE::WHITE_BIG) {
		setIsTransforming(true);
		currentMode = WHITE_BIG;
	}

	if (currentMode == WHITE_BIG && GameConfig::getInstance().marioState == MARIO_STATE::SMALL) {
		setIsTransforming(true);
		currentMode = SMALL;
	}

	if (deadthTimer > 2.5) GameConfig::getInstance().levelStatus = RESTART, health = 1, deadthTimer = 0, isDead = false;

	shootTimer -= deltatime;
	if (shootTimer < 0) shootTimer = 0;


	if (currentState) {
		//std::cout << "Current state exists" << std::endl;
		currentState->handle(this, deltatime);
		currentState->update(this, deltatime);
	}

	if (health <= 0) {
		isDead = true;
		if (health == 0) setVel({ 0, -180.0f }), health--;
		deadthTimer += deltatime;
		setPos(getPos() + getVel() * deltatime);
		performPhysics(deltatime);
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
		if (en->getType() == ENEMY && !isInvincible) {
			if (dir == TOP) setVel({ getVel().x, -80 }), en->inflictDamage(), isKilling = true;
			en->affectOther(this);
			continue;
		}
		else if (isInvincible) {
			if (dir == TOP || dir == BOTTOM || dir == LEFT || dir == RIGHT) en->inflictDamage();
		}
		en->affectOther(this, deltatime);
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
			if (dir == dir::TOP) isJumping = false;
			sf::Vector2f center = tile->getHitbox().pos + tile->getHitbox().size / 2.f;
			float dist = (pcenter.x - center.x) * (pcenter.x - center.x) + (pcenter.y - center.y) * (pcenter.y - center.y);
			if (dist < curDist) curDist = dist, cur = tile;
		}

		if (cur) cur->affectOther(this, deltatime);
	}

	performPhysics(deltatime);
}

void Player::jump(float deltatime) {
	if (isDead) return;
	if (isOnGround && !isJumping) {
		SoundManager::getInstance().playSound("jump");
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
	facing = -1;

	float capSpeed = -140;

	if (!isOnGround && getVel().x > capSpeed / 2) capSpeed /= 4;

	setVel({ getVel().x + -7, getVel().y });
	if (getVel().x < capSpeed) setVel(sf::Vector2f(capSpeed, getVel().y));
}

void Player::shoot(float deltatime) {
	if (currentMode != WHITE_BIG) return;
	if (shootTimer <= 0.5) {
		EntityManager::getInstance().addEntity(new Fireball(getPos(), sf::Vector2f(4, 4), getFacing()));
		shootTimer = 1;
	}
}

void Player::dodge(float deltatime, bool isDoged) {
	if (currentMode == SMALL) return;
	if (isDoged) {
		isDodging = true;
		setState("DODGE");
	} else {
		isDodging = false;
	};
}


void Player::moveRight(float deltatime) {
	if (isDead) return;
	facing = 1;
	//setVel(sf::Vector2f(140, getVel().y));
	float capSpeed = 140;
	if (!isOnGround && getVel().x < capSpeed / 2) capSpeed /= 4;
	setVel({ getVel().x + 7, getVel().y });
	if (getVel().x > capSpeed) setVel(sf::Vector2f(capSpeed, getVel().y));
}

int Player::getType() {
	return PLAYER;
}

void Player::inflictDamage() {

	if (isTransforming) return;

	if (currentMode == BIG || currentMode == WHITE_BIG) {
		GameConfig::getInstance().marioState = MARIO_STATE::SMALL;
		setIsTransforming(true);
		return;
	}

	if (getIsTransforming()) return;
	health--;
}

void Player::setPos(sf::Vector2f pos) {
	Actor::setPos(pos);
	setSpritePos(pos - sf::Vector2f(2, 2));
}

void Player::reset() {
	isRenderSprite = true;
	isRenderHitbox = true;
	isTransforming = false;
	facing = 1;
	currentMode = SMALL;
	setSize(sf::Vector2f(14, 14));
	setState("IDLE");
	obstacle.clear();
	nearPointerTiles.clear();
	otherEntities.clear();
	setVel(sf::Vector2f(0, 0));
}

bool Player::getIsDodge() const {
	return isDodging;
}