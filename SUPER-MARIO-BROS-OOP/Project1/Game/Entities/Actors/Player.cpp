#include "Player.h"


Player::Player() {
	throw std::exception("Need to init the rigth construtor for player");
}

Player::Player(sf::Vector2f pos, sf::Vector2f size) : Actor(pos, size) {
	isRenderSprite = true;
	isRenderHitbox = false;
	facing = 1;
	spriteFace = 1;
	currentState = IDLE;
	currentMode = SMALL;

	ani[1][IDLE] = {"right-small-mario-6"};
	ani[1][JUMP] = {"right-small-mario-4"};
	ani[1][RUN] = {
		"right-small-mario-0",
		"right-small-mario-1",
		"right-small-mario-2",
	};

	ani[1][SLIDE] = {"right-small-mario-3"};
	ani[1][DIE] = {"right-small-mario-5"};
	ani[1][KILL] = { "right-small-mario-7" };


	ani[0][IDLE]= { "left-small-mario-7" };
	ani[0][JUMP]= { "left-small-mario-9" };
	ani[0][RUN]= {
		"left-small-mario-13",
		"left-small-mario-12",
		"left-small-mario-11",
	};
	ani[0][SLIDE] = { "left-small-mario-10" };
	ani[0][DIE] = { "left-small-mario-8" };
	ani[0][KILL] = { "left-small-mario-6" };

	setTexture("mario", "right-small-mario-6"); // idle right
}


void Player::update(float deltatime) {
	animation(deltatime);

	sf::Vector2f vx = getVel();
	int isCollide = resolveCollideGround(obstacle, deltatime);

	if (getPos().y > 800) setVel(sf::Vector2f(getVel().x, 0));
	isOnGround = isCollide & (1 << 2);

	if (facing == 0 && isOnGround) currentState = IDLE;

	if (isOnGround)
		setFric({ 3, 0 }), isJumping = false;
	else
		setFric({ 0, 0 });

	if (getVel().x == 0 && isOnGround)
		currentState = IDLE; else
		if (!isOnGround)
			currentState = JUMP; else
			if (getVel().x * facing < 0)
				currentState = SLIDE; 
			else
				currentState = RUN;


	setPos(getPos() + getVel() * deltatime);
	setSpritePos(getPos() - sf::Vector2f{ 2, 2 });

	if (isCollide & 5) // touch top or bottom
		setVel({ getVel().x, 0 }), isJumping = false;

	std::vector <Entity*> other = otherEntities;

	for (const auto& en : other) { // player interact with surrounding enemies
		int dir = dynamicRectVsRect(getHitbox(), deltatime, getVel() - en->getHitbox().vel, en->getHitbox());
		if (dir == -1) continue;
		if (en->getType() == ENEMY) {

			// if the contact direction is on top of enemy player will inflict a damage
			if (dir == TOP) setVel({ getVel().x, -20 }), en->inflictDamage(), currentState = KILL;
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
			int dir = dynamicRectVsRect(getHitbox(), deltatime, getVel() - tile->getHitbox().vel, tile->getHitbox());
			if (dir == -1) continue;
			sf::Vector2f center = tile->getHitbox().pos + tile->getHitbox().size / 2.f;			
			float dist = (pcenter.x - center.x) * (pcenter.x - center.x) + (pcenter.y - center.y) * (pcenter.y - center.y);
			if (dist < curDist) curDist = dist, cur = tile;	
		}

		if (cur) cur->affectOther(this, deltatime);
	}

	performPhysics(deltatime);
}

void Player::jump(float deltatime) {
	currentState = JUMP;
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

void Player::moveRight(float deltatime) {
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

ENTITY_TYPE Player::getType() {
	return PLAYER;
}

void Player::inflictDamage() {
	health--;
}


void Player::animation(float deltatime) {
	bool isRight = facing == 1;
	if (doesItKill) currentState = KILL;
	setTexture("mario", ani[isRight][currentState][aniLoop % ani[isRight][currentState].size()]);

	timer += deltatime;
	if (doesItKill && timer < 0.2) return;
	if (currentState == KILL && !doesItKill) {
		doesItKill = 1;
	}
	else {
		doesItKill = 0;
	}

	if (timer > 0.15)
		aniLoop++, timer = 0;
}
