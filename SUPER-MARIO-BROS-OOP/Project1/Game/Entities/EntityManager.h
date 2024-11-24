#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class EntityManager {
private:
    std::vector <Entity*> entities;  // Container to store entities
    int curEntity = 0;
public:

    ~EntityManager();
    // Add an entity to the manager -> if an entity A derive from class entity -> addEntity(new A())
    void addEntity(Entity* entity);

    // Render all entities
    void updateAll(float deltaTime);

    void renderAll(sf::RenderWindow* window);
    // vector <..> getEntityWithID();
};