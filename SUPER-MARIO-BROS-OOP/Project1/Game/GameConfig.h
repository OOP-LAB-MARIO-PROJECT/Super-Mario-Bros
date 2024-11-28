#pragma once
#include <map>
#include <SFML/Graphics.hpp>


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

    WORLD currentWorld = OVERWORLD;
    float cameraBase = 192;

    // Configurations
    float volume = 100.0f; // Default volume (0-100)
    std::string playerName = "Player"; // Default player name
    std::string currentLevel = "Level 1"; // Current level name
    int score = 0; // Player's score
    int coins = 0; // Number of coins collected
    int timeLeft = 300; // Remaining time in seconds
    
    std::map<std::string, sf::Keyboard::Key> controls;
    // Methods
    void setVolume(float newVolume);
    void toggleVolume();
    void setPlayerName(const std::string& name);
    void setCurrentLevel(const std::string& level);
    void addScore(int points);
    void addCoin();
    void setTimeLeft(int seconds);
    void updateControl(const std::string& action, sf::Keyboard::Key key);
    sf::Keyboard::Key getControl(const std::string& action);
};

