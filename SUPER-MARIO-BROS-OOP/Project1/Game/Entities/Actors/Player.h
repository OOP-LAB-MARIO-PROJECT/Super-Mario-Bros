#pragma once
#include "Actor.h"
#include <vector>
#include <exception>
#include <map>
#include "../Actors/AnimationState/AnimationState.h"

class Player : public Actor
{
	std::shared_ptr<AnimationState> currentState;
	std::map<std::string, std::shared_ptr<AnimationState>> stateCache;
	int health = 1;
	int moving = 0;
	bool reachMaxHeight = false;
	bool isJumping = false;
	int speed = 100;
	ENTITY_TYPE currentType = PLAYER;
	float deadthTimer = 0;

public:
	std::vector <Entity*> nearPointerTiles;
	
	enum mode {
		SMALL,
		LARGE,
		WHITE_LARGE
	} currentMode;

	Player();

	Player(sf::Vector2f pos, sf::Vector2f size);


	void setState(const std::string& stateName) override;
	void update(float deltatime) override;
	void inflictDamage() override;
	void setPos(sf::Vector2f pos) override;
	void jump(float deltatime);
	void notJump(float deltatime);
	void moveLeft(float deltatime);
	void moveRight(float deltatime);
	ENTITY_TYPE getType() override;
};

