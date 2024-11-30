#include "Entity.h"


void Entity::updateEvironment(const std::vector <Hitbox>& obstacle, const std::vector <Entity*>& otherEntities) {
	this->obstacle = obstacle;
	this->otherEntities = otherEntities;
}


void Entity::setRenderHitbox(bool f) { isRenderHitbox = f; }
void Entity::setRenderSprite(bool f) { isRenderSprite = f; }



void Entity::setPos(sf::Vector2f pos) {
	hitbox.pos = pos;
}

void Entity::setSize(sf::Vector2f size) {
	hitbox.size = size;
}

void Entity::setVel(sf::Vector2f vel) {
	hitbox.vel = vel;
}

void Entity::affectOther(Entity* other) {
}

void Entity::affectOther(Entity* other, float deltatime) {
}

void Entity::affectOther(Entity* other, float deltaTime) {

}
