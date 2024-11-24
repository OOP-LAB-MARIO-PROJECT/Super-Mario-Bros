#include "EntityManager.h"

void EntityManager::addEntity(Entity* entity) {
	entities.push_back(entity);
}

// Render all entities
void EntityManager::updateAll(float deltaTime) {
	for (auto en : entities) en->update(deltaTime);
}

void EntityManager::renderAll(sf::RenderWindow* window) {
	for (auto en : entities) en->render(window);
}

EntityManager::~EntityManager() {
	for (auto x : entities)
		delete x;
}