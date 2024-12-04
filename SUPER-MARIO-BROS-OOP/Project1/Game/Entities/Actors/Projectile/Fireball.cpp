#include "Fireball.h"
#include <exception>

Fireball::Fireball() : Projectile() {
	throw std::exception("cannot create an projectile without position");
}

Fireball::Fireball(sf::Vector2f pos) {
	hitbox.size = sf::Vector2f(5, 5);
	isRenderHitbox = true;
}

Fireball::Fireball(sf::Vector2f pos, sf::Vector2f size, int facing) : Projectile(pos, size) {
	hitbox.size = size;
	hitbox.pos = pos;
	timeToLive = 10;
	if (facing == 1) setVel(sf::Vector2f(80, 0));
	if (facing == -1) setVel(sf::Vector2f(-80, 0));
	setGravity(sf::Vector2f(0, 400));
	setFric(sf::Vector2f(0, 0));
	isRenderHitbox = true;
}


void Fireball::update(float deltatime) {
	if ((timeToLive -= deltatime) <= 0) kill();
	
	performPhysics(deltatime);
	std::cout << obstacle.size() << '\n';
	for (auto& ob : obstacle) {

		sf::RectangleShape tmp;
		tmp.setFillColor(sf::Color::Yellow);
		tmp.setSize(ob.size);
		tmp.setPosition(ob.pos);
		sf::RenderWindow* debug = EntityManager::getInstance().debugWindow;
		if (debug) {
			debug->draw(tmp);
		}
		int dir = dynamicRectVsRect(hitbox, deltatime, hitbox.vel, ob);
		if (dir == -1) continue;
		if (dir == TOP || dir == BOTTOM) setVel(sf::Vector2f(getVel().x, -100));
		if (dir == LEFT || dir == RIGHT) kill();
	}

	setPos(getPos() + getVel() * deltatime);
}