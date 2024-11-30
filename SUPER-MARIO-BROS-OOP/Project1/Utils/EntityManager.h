#pragma once
#include "../Game/Entities/Entity.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class EntityManager {
private:
    std::vector <Entity*> entities;  // Container to store entities
    sf::Vector2f updatePivot = { 0, 0 };
    float updateDistance = 600;
    int curEntity = 0;

    ~EntityManager();
    EntityManager() = default; // Private constructor
public:

    EntityManager(const EntityManager&) = delete;
    EntityManager& operator=(const EntityManager&) = delete;

    static EntityManager& getInstance() {
        static EntityManager instance; // Guaranteed to be lazy-initialized and thread-safe
        return instance;
    }
    // Add an entity to the manager -> if an entity A derive from class entity -> addEntity(new A())
    void addEntity(Entity* entity);
    // Render all entities
    void updateAll(float deltaTime);

    void renderAll(sf::RenderWindow* window);
    // vector <..> getEntityWithID();

    void setUpdatePivot(sf::Vector2f pos);
    std::vector <Entity*>& getEntities();  // Container to store entities

    // get near entity to this "en"
    std::vector<Entity*> getNearEntity(Entity* en, float radius = 500);

    void filter(); // filter out dead entities
    void clear(); // clear out entities

};