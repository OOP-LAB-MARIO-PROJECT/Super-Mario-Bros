#pragma once
class GameConfig {

    GameConfig() = default;
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

public: 

    static GameConfig& getInstance() {
        static GameConfig instance;
        return instance;
    }
};

