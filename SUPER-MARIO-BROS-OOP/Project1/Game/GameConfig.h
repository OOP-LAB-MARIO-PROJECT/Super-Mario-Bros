#pragma once
#include <map>

// Glolbal configuration for Game -> not implement
class GameConfig {

    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

public: 

    static GameConfig& getInstance() {
        static GameConfig instance;
        return instance;
    }

    float volume;
};

