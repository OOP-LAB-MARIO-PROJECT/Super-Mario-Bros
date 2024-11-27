#include "Goompa.h"
#include <vector>

Goompa::Goompa(sf::Vector2f pos, sf::Vector2f size) : Enemy(pos, size) {
	isRenderHitbox = true;
	facing = 1;
}

void Goompa::update(float deltatime) {
	//std::vector <Hitbox> obstacle = map->getNearTiles(getPos() + getSize() / 2.f);
	//std::vector <Entity*> otherEntities = map->getNearEntity(this);

	for (auto en : otherEntities) {
		Hitbox ob = en->getHitbox();
		ob.vel = sf::Vector2f{ 0.f, 0.f };
		obstacle.push_back(ob);
	}
	

	int dir = resolveCollideGround(obstacle, deltatime);
	setPos(getPos() + getVel() * deltatime); // update right after collision for best resolution

	// 1 << 3 = right

	if (dir & (1 << 2)) setVel({ getVel().x, 0 });
	if (dir & (1 << 3)) facing = 1, setVel(sf::Vector2f(50, getVel().y));
	if (dir & (1 << 1)) facing = -1, setVel(sf::Vector2f(-50, getVel().y));

	if (!(dir & (1 << 1)) && !(dir & (1 << 3))) {
		if (facing == 1)
			setVel(sf::Vector2f(50, getVel().y));
		else
			setVel(sf::Vector2f(-50, getVel().y));
	}

	// 1 << 1 = left 
	behavior(deltatime);
	performPhysics(deltatime);
}

void Goompa::behavior(float deltatime) {
	if (health <= 0) {
		kill();
		return;
	}
}

ENTITY_TYPE Goompa::getType() {
	return ENEMY;
}

void Goompa::inflictDamage() {
	health--;
}
