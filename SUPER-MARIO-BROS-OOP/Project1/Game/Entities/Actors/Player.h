#pragma once
#include "Actor.h"
#include "../Map.h"
#include <vector>
#include <exception>
#include <map>
class Map;

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
	Map* map = NULL;
	
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
	Player() {
		throw std::exception("Need to init the rigth construtor for player");
	}

	Player(sf::Vector2f pos, sf::Vector2f size, Map* map);

	void update(float deltatime) override;
	void inflictDamage() override;
	
	void jump(float deltatime);
	void notJump(float deltatime);
	void moveLeft(float deltatime);
	void moveRight(float deltatime);
	void animation(float deltatime);
	ENTITY_TYPE getType() override;
};

