#include "EntityManager.h"

void EntityManager::addEntity(Entity* entity) {
	if (entity == NULL) return;
	tempEn.push_back(entity);
}

// Render all entities
void EntityManager::updateAll(float deltaTime) {
	for (auto en : entities) {
		if (!en->isDead() && std::abs(en->getHitbox().pos.x - updatePivot.x) < (float)updateDistance) {
			en->update(deltaTime);
		}
	}

	for (auto en : tempEn) {
		entities.push_back(en);
		quadEn.insert(en);
	}

	tempEn.clear();
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
	space.pos -= space.size;
	space.size *= 2.f;

	res = quadEn.nearEntity(space);
	for (auto x : res) if (!x->isDead()) tmp.push_back(x);
	return tmp;
}

void EntityManager::filter() {
	std::vector <Entity*> filtered;
	for (auto& en : entities) 
		if (en->isDead()) {
			en->notify(en);
			delete en;
		}
		else {
			filtered.push_back(en);
		}
	entities = filtered;
}

std::vector <Entity*>& EntityManager::getEntities() {
	return entities;
}

void EntityManager::clear() {
	for (auto x : entities)
		delete x;
	entities.clear();
	quadEn.root = nullptr;
}

void EntityManager::setSpace(float width, float height) {
	quadEn.init(width, height, 8);
}


void EntityManager::updatePositionAndPhysic(float deltaTime) {
	for (int i = 0; i < entities.size(); i++) {
		entities[i]->updatePositionAndPhysic(deltaTime);
	}
}