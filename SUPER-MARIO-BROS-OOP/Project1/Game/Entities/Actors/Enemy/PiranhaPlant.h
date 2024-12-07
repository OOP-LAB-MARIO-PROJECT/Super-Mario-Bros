#pragma once
#include "Enemy.h"
#include <vector>
#include <map>
#include "../AnimationState/AnimationState.h"
/*

simple testing enemy
*/
class PiranhaPlant : public Enemy
{
	std::shared_ptr<AnimationState> currentState;
	std::map<std::string, std::shared_ptr<AnimationState>> stateCache;
	int health = 1;
	int facing = 0;
	float timer = 0;
	int aniLoop = 0;
	float jumpingTime = 0;
	float deathTimer = 0;
	float dist = 0;
	float cnt = 0;
	sf::Vector2f a;
	bool isStop = false;
	float tmp = 0;
public:


	void setState(const std::string& stateName) override;
	PiranhaPlant(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void inflictDamage() override;
	void affectOther(Entity* other, float deltatime) override;
	int getHealth() override;
	void setHealth(int h) override;
	int getType() override;
};
