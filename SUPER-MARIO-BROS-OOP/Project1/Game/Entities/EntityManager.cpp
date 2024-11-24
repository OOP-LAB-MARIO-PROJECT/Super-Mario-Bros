#include "EntityManager.h"

void EntityManager::addEntity(Entity* entity) {
	entities.push_back(entity);
}

// Render all entities
void EntityManager::updateAll(float deltaTime) {
	for (auto en : entities) 
		if (std::abs(en->getHitbox().pos.x - updatePivot.x) < (float)updateDistance) en->update(deltaTime);
}

void EntityManager::renderAll(sf::RenderWindow* window) {
	for (auto en : entities) en->render(window);
}

EntityManager::~EntityManager() {
	for (auto x : entities)
		delete x;
}

void EntityManager::setUpdatePivot(sf::Vector2f pos) {
	updatePivot = pos;
}

std::vector<Entity*> EntityManager::getNearEntity(Entity* en) {
	std::vector <Entity*> res;
	auto dist = [&](sf::Vector2f a, sf::Vector2f b) {
		return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
	};

	for (auto entity : entities) if (entity != en && dist(entity->getHitbox().pos, en->getHitbox().pos) < 2500) {
		res.push_back(entity);
	}
	return res;
}