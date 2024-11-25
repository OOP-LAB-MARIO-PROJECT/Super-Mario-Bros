#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <iostream>

#include "../Game/Scenes/Scene.h"


class SceneManager {
public:
    enum class Scenes
    {
        Game,
        Exit,
        Home,
        Pause,
        Login,
        Register,
    };

    static SceneManager& getInstance();

    Scenes getCurrentScene();
    void addScene(Scenes sceneId, Scene* scene);
    void deleteScene(Scenes sceneId);
    void navigateTo(Scenes scene);
    void update(float deltatime = 0.f);
    void render();
    ~SceneManager();

private:
    std::map<Scenes, Scene*> sceneRegistry; // Renamed the map
    Scenes currentScene = Scenes::Login;   // Default starting scene
    SceneManager();
    // Prevent copying and assignment
    SceneManager(SceneManager const&) = delete;
    SceneManager& operator=(SceneManager const&) = delete;
};
