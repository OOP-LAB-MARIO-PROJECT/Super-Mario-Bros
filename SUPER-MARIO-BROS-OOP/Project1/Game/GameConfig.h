#pragma once
#include <map>



enum WORLD {
    OVERWORLD,
    UNDERGROUND
};


// Glolbal configuration for Game -> not implement
class GameConfig {

    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;
    ~GameConfig() = default;

public: 

    static GameConfig& getInstance() {
        static GameConfig instance;
        return instance;
    }

    float volume;
    WORLD currentWorld = OVERWORLD;
    float cameraBase = 192;
};

