#pragma once
#include <string>
#include <map>

class GameConfig {
private:
    GameConfig() = default; // Private constructor for Singleton
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

public:
    static GameConfig& getInstance() {
        static GameConfig instance;
        return instance;
    }

    // Configurations
    float volume = 100.0f; // Default volume (0-100)
    std::string playerName = "Player"; // Default player name
    std::string currentLevel = "Level 1"; // Current level name
    int score = 0; // Player's score
    int coins = 0; // Number of coins collected
    int timeLeft = 300; // Remaining time in seconds
    std::map<std::string, sf::Keyboard::Key> controls = { // Default controls
        {"MoveLeft", sf::Keyboard::A},
        {"MoveRight", sf::Keyboard::D},
        {"Jump", sf::Keyboard::Space}
    };

    // Methods
    void setVolume(float newVolume) {
        if (newVolume >= 0.0f && newVolume <= 100.0f) {
            volume = newVolume;
        }
    }

    void toggleVolume() {
        volume = (volume > 0.0f) ? 0.0f : 100.0f; // Toggle between mute and full volume
    }

    void setPlayerName(const std::string& name) {
        playerName = name;
    }

    void setCurrentLevel(const std::string& level) {
        currentLevel = level;
    }

    void addScore(int points) {
        score += points;
    }

    void addCoin() {
        coins++;
    }

    void setTimeLeft(int seconds) {
        if (seconds >= 0) {
            timeLeft = seconds;
        }
    }

    void updateControl(const std::string& action, sf::Keyboard::Key key) {
        if (controls.find(action) != controls.end()) {
            controls[action] = key;
        }
    }

    sf::Keyboard::Key getControl(const std::string& action) {
        return controls[action];
    }
};
