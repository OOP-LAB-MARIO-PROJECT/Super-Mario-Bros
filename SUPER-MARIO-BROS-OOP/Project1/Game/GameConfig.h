#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "../Utils/json.hpp"

// Glolbal configuration for Game -> every file can get infomation from this

enum WORLD {
    OVERWORLD,
    UNDERGROUND
};

enum MARIO_STATE {
    BIG,
    SMALL,
    WHITE_BIG,
    INVINCIBLE
};

enum LEVEL_STATUS {
    PLAYING,
    RESTART,
    NEXT_LEVEL,
    IDLE
};

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

    // Game status
    
    WORLD currentWorld = OVERWORLD;
    MARIO_STATE marioState = SMALL;
    LEVEL_STATUS levelStatus = PLAYING;
    float cameraBase = 192;

    // Configurations
    bool hasKeyChanges = false;
    std::map<std::string, std::string> mapList;
    std::map<std::string, sf::Keyboard::Key> controls;
    std::map <std::string, std::pair<int, int>> unlockedLevel;
    std::string playerName = "Player"; // Default player name
    std::string currentLevel = "Level 1"; // Current level name
    std::string nextLevel = "";
    float volume = 100.0f; // Default volume (0-100)
    int timeLeft = 300; // Remaining time in seconds
    int score = 0; // Player's score
    int coins = 0; // Number of coins collected
    
    // Methods
    void setVolume(float newVolume);
    void toggleVolume();
    void setPlayerName(const std::string& name);
    void setCurrentLevel(const std::string& level);
    void setNextLevel(const std::string& level);
    void addScore(int points);
    void addCoin();
    void setTimeLeft(int seconds);
    void updateControl(const std::string& action, sf::Keyboard::Key key);
    sf::Keyboard::Key getControl(const std::string& action);
    
    
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void loadFromFile();
    void saveToFile();
    void saveLevel();
};

