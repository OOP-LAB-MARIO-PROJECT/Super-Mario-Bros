#pragma once
#include "Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class EntityManager {
private:
    std::vector <Entity*> entities;  // Container to store entities
    sf::Vector2f updatePivot = { 0, 0 };
    float updateDistance = 200;
    int curEntity = 0;

public:

    ~EntityManager();
    // Add an entity to the manager -> if an entity A derive from class entity -> addEntity(new A())
    void addEntity(Entity* entity);
    
    // Render all entities
    void updateAll(float deltaTime);

    void renderAll(sf::RenderWindow* window);
    // vector <..> getEntityWithID();

    void setUpdatePivot(sf::Vector2f pos);

    // get near entity to this "en"
    std::vector<Entity*> getNearEntity(Entity* en, float radius = 50);

    void filter(); // filter out dead entities
};