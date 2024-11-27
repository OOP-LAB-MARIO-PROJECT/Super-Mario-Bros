#pragma once
#include "Actor.h"
#include <vector>
#include <exception>
#include <map>

class Player : public Actor
{
	int facing = 0;
	int spriteFace = 1;
	int health = 0;
	int moving = 0;
	bool reachMaxHeight = false;
	bool isJumping = false;
	int speed = 100;
	float timer = 0;
	
	ENTITY_TYPE currentType = PLAYER;
	enum state {
		RUN,
		IDLE,
		SLIDE,
		JUMP,
		DIE,
		KILL,
	} currentState;
	
	int doesItKill = 0;
	// animation list
	std::map <state, std::vector <std::string>> ani[2];
	int aniLoop = 0; 

public:
	std::vector <Entity*> nearPointerTiles;
	
	enum mode {
		SMALL,
		LARGE,
		WHITE_LARGE
	} currentMode;

	Player();

	Player(sf::Vector2f pos, sf::Vector2f size);

	void update(float deltatime) override;
	void inflictDamage() override;
	
	void jump(float deltatime);
	void notJump(float deltatime);
	void moveLeft(float deltatime);
	void moveRight(float deltatime);
	void animation(float deltatime);
	ENTITY_TYPE getType() override;
};

