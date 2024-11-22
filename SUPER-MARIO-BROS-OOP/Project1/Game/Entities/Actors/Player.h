#pragma once
#include "Actor.h"

class Player : public Actor
{
	int facing = 0;
	int health = 0;
	int moving = 0;
	bool reachMaxHeight = false;
	bool isJumping = false;
	int speed = 100;

public:
	
	Player(sf::Vector2f pos, sf::Vector2f size);

	void update(float deltatime) override;
	
	void jump(float deltatime);
	void notJump(float deltatime);
	void moveLeft(float deltatime);
	void moveRight(float deltatime);

};

