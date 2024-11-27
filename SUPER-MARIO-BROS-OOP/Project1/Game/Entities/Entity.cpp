#include "Entity.h"


void Entity::updateEvironment(const std::vector <Hitbox>& obstacle, const std::vector <Entity*>& otherEntities) {
	this->obstacle = obstacle;
	this->otherEntities = otherEntities;
}


void Entity::setRenderHitbox(bool f) { isRenderHitbox = f; }
void Entity::setRenderSprite(bool f) { isRenderSprite = f; }