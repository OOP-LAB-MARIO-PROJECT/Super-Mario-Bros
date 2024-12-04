#include "Physics.h"

#define vt sf::Vector2f

void Physics::setGravity(vt f) { g = f; }

vt Physics::getVel() const { return vel; }


void Physics::setVel(vt f) { vel = f; }

void Physics::setFric(vt f) { fric = f; }

void Physics::performPhysics(float dt) {
	if (vel.x < 0) {
		vel += fric;
		if (vel.x > 0) vel.x = 0;
	}
	else {
		vel -= fric;
		if (vel.x < 0) vel.x = 0;
	}
	vel += g * dt;
	if (vel.y > 0 && vel.y < minGravity) vel.y = minGravity;
}


#undef vt