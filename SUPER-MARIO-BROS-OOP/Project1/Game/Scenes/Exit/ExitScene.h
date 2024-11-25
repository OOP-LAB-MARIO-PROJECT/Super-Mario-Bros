#pragma once

#include "../Scene.h"
#include "../../../Utils/SceneManager.h"

class ExitScene : public Scene {
private: 
public:

    ExitScene(sf::RenderWindow* window) : Scene(window) {
    
    };
    ~ExitScene() {};
    void update(float deltatime) override {
        getWindow()->close();
    }
};

