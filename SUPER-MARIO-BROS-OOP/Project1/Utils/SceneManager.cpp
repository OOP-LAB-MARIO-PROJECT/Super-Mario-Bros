#include "SceneManager.h"

// Singleton instance
SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}

SceneManager::~SceneManager() {}

SceneManager::SceneManager() {}

// Returns the current scene ID
SceneManager::Scenes SceneManager::getCurrentScene()
{
    return currentScene;
}

// Adds a new scene to the map
void SceneManager::addScene(Scenes sceneId, unique_ptr<Scene> scene)
{
    sceneRegistry[sceneId] = move(scene);
}

// Deletes a scene from the map
void SceneManager::deleteScene(Scenes sceneId)
{
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
        cout << "Scene not found: " << static_cast<int>(scene) << endl;
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

