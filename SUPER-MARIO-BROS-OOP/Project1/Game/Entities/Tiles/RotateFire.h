#pragma once
#include "Tile.h"
#include "../Actors/Enemy/Enemy.h"
#include "../../../Utils/EntityManager.h"

#define PI 3.14159

class RotateFireBall : public Enemy {
	std::vector <std::string> animation;
	int loop = 0;
	float timer = 0;
public:
	RotateFireBall(sf::Vector2f pos) : Enemy(pos, sf::Vector2f(4, 4)) {
		animation = {
			"fireball-0",
			"fireball-1",
			"fireball-2",
			"fireball-3"
		};

		setTexture("8-bit-block", animation[loop]);
		autoSpriteFollowHitbox = true;
	}


	void update(float deltatime) override {
		timer -= deltatime;
		if (timer < 0) {
			loop++;
			if (loop > 3) loop = 0;
			timer = 0.2;
			setTexture("8-bit-block", animation[loop]);
			//std::cout << "asdflaksjhfiwue\n";
		}
	}

	void affectOther(Entity* other) override {
		Collision::rect a = { other->getHitbox().pos, other->getHitbox().size };
		Collision::rect b = { this->getHitbox().pos, this->getHitbox().size};
		other->inflictDamage();
		std::cout << "okok\n";
	}

	void setPos(sf::Vector2f nPos) override {
		Actor::setPos(nPos);
	}

	void behavior(float deltatime) override {}

	int getType() override{
		return ENTITY_TYPE::ENEMY;
	}
};

class RotateFire : public Tile {
	std::vector <RotateFireBall*> fireballs;
	int numBalls;
	sf::Vector2f center;
	float angle = 0;
public:
	RotateFire(sf::Vector2f _pos, sf::Vector2f _size, int num) : Tile(_pos, _size, false), numBalls(num) {
		center = _pos + _size / 2.f;
		// Thay đổi vị trí center để đảm bảo nó nằm đúng ngay chỗ block4
		center.y += 0.1 * numBalls;
		center.x -= numBalls;
		for (int i = 0; i < numBalls; i++) {
			fireballs.push_back(new RotateFireBall(center));
			fireballs[i]->setRenderSprite(true);
			EntityManager::getInstance().addEntity(fireballs[i]);
		}
	}

	void update(float deltatime) override {
		angle += deltatime;
		if (angle > 2 * PI) angle = 0;
		for (int i = 0; i < numBalls; i++) {
			float len = i * 8;
			sf::Vector2f position(center.x + len * std::cos(angle), center.y + len * std::sin(angle));
			fireballs[i]->setPos(position);
		}
		for (auto& fireball : fireballs) { 
			fireball->update(deltatime); 
		}
	}
	void renderExtra(sf::RenderWindow* window) const override { 
		for (auto& fireball : fireballs) { 
			fireball->render(window); 
		} 
	}
};

