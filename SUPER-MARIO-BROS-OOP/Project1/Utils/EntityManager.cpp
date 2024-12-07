#include "EntityManager.h"

void EntityManager::addEntity(Entity* entity) {
	if (entity == NULL) return;
	entities.push_back(entity);
	quadEn.insert(entity);
}

// Render all entities
void EntityManager::updateAll(float deltaTime) {
	//std::vector <Entity*> alive;
	for (auto en : entities)
		if (!en->isDead() && std::abs(en->getHitbox().pos.x - updatePivot.x) < (float)updateDistance) {
			en->update(deltaTime);
		}

	for (auto en : entities) en->notify(en);
	quadEn.checkForPending();
}

void EntityManager::renderAll(sf::RenderWindow* window) {
	for (auto en : entities) 
		if (!en->isDead()) 
			en->render(window);
}

EntityManager::~EntityManager() {
	for (auto x : entities)
		delete x;
}

void EntityManager::setUpdatePivot(sf::Vector2f pos) {
	updatePivot = pos;
}

std::vector<Entity*> EntityManager::getNearEntity(Entity* en, float radius) {
	std::vector <Entity*> res;
	std::vector <Entity*> tmp;
	
	Hitbox space = en->getHitbox();
	space.pos -= space.size * 4.f;
	space.size *= 4.f;

	res = quadEn.nearEntity(space);
	for (auto x : res) if (!x->isDead()) tmp.push_back(x);
	return tmp;
}

void EntityManager::filter() {
	std::vector <Entity*> filtered;
	for (auto& en : entities) 
		if (en->isDead()) {
			delete en;
		}
		else {
			filtered.push_back(en);
		}
	entities = filtered;
}

std::vector <Entity*>& EntityManager::getEntities() {
	// Container to store entities
	return entities;
}

void EntityManager::clear() {
	// clear out entities
	for (auto x : entities)
		delete x;
	entities.clear();
	quadEn.root = nullptr;
}

void EntityManager::setSpace(float width, float height) {
	quadEn.init(width, height, 10);
}
