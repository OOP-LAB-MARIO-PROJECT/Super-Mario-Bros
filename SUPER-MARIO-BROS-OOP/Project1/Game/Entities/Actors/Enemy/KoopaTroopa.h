#pragma once
#include "Enemy.h"
#include <vector>
#include <map>
#include "../AnimationState/AnimationState.h"
/*

simple testing enemy
*/
class KoopaTroopa : public Enemy
{
	std::shared_ptr<AnimationState> currentState;
	std::map<std::string, std::shared_ptr<AnimationState>> stateCache;
	int health = 2;
	float timer = 0;
	int aniLoop = 0;
	bool isDefense = false;
	float jumpingTime = 0;
	float deathTimer = 0;
	float speed = 50;
	int cnt;
	bool isHarm = false;
public:


	void setState(const std::string& stateName) override;
	KoopaTroopa(sf::Vector2f pos, sf::Vector2f size);
	void update(float deltatime) override;
	void behavior(float deltatime) override;
	void inflictDamage() override;
	void affectOther(Entity* other, float deltatime) override;

	int getType() override;
};
