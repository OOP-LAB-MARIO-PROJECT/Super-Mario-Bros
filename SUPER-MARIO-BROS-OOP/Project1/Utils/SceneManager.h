#pragma once
#include "../Game/Scenes/Scene.h"
#include <map>
#include <memory>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class SceneManager
{
public:
    enum class Scenes
    {
        Game,
        Exit,
        Home,
        Pause,
    };

    static SceneManager& getInstance();

    Scenes getCurrentScene();
    void addScene(Scenes sceneId, unique_ptr<Scene> scene);
	void deleteScene(Scenes sceneId);
    void navigateTo(Scenes scene);
    void update();
    void render();
    ~SceneManager();

private:
    map<Scenes, unique_ptr<Scene>> sceneRegistry; // Renamed the map
    Scenes currentScene = Scenes::Home;   // Default starting scene
    SceneManager();
    // Prevent copying and assignment
    SceneManager(SceneManager const&) = delete;
    SceneManager& operator=(SceneManager const&) = delete;
};

