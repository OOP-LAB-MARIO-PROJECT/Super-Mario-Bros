#pragma once
#include "../Scene.h"
#include "../../Utils/SceneManager.h"
#include "../../../UI_Components/Button.h"

class HomeScene : public Scene
{
};


    void loopEvents();
    void drawMenu();
    void update(float deltatime) override;
};