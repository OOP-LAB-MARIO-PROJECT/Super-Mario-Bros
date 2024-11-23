#include "SceneManager.h"

// Singleton instance
SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

SceneManager::~SceneManager() {
    for (auto& x : sceneRegistry)
        delete x.second;
}

SceneManager::SceneManager() {
    currentScene = Scenes::Home;
}

// Returns the current scene ID
SceneManager::Scenes SceneManager::getCurrentScene()
{
    return currentScene;
}

// Adds a new scene to the map
void SceneManager::addScene(Scenes sceneId, Scene* scene)
{
    sceneRegistry[sceneId] = scene;
}

// Deletes a scene from the map
void SceneManager::deleteScene(Scenes sceneId)
{
    std::cout << "called delete" << '\n';
    sceneRegistry.erase(sceneId);
}

// Switches to a specified scene
void SceneManager::navigateTo(Scenes scene)
{
    if (sceneRegistry.find(scene) != sceneRegistry.end()) // Check if the scene exists
    {
        currentScene = scene;
    }
    else
    {
        // Handle error (scene not found)
        std::cout << "Scene not found: " << static_cast<int>(scene) << std::endl;
    }
}

// Updates the current scene
void SceneManager::update(float deltatime)
{
    if (sceneRegistry.find(currentScene) != sceneRegistry.end())
    {
        sceneRegistry[currentScene]->update(deltatime); // Call update for the current scene
    }
}

// Renders the current scene
void SceneManager::render()
{
    if (sceneRegistry.find(currentScene) != sceneRegistry.end())
    {
        sceneRegistry[currentScene]->display(); // Call display for the current scene
    }
}
