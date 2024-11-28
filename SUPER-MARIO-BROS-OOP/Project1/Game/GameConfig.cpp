#include "GameConfig.h"
#include <iostream>

// Singleton instance is managed within the header file (no explicit code needed here)

// Set volume (0-100)
void GameConfig::setVolume(float newVolume) {
    if (newVolume >= 0.0f && newVolume <= 100.0f) {
        volume = newVolume;
    }
    else {
        std::cerr << "Volume out of range. Must be between 0 and 100.\n";
    }
}

// Toggle volume (mute/unmute)
void GameConfig::toggleVolume() {
    volume = (volume > 0.0f) ? 0.0f : 100.0f;
}

// Set the player's name
void GameConfig::setPlayerName(const std::string& name) {
    if (!name.empty()) {
        playerName = name;
    }
    else {
        std::cerr << "Player name cannot be empty.\n";
    }
}

// Set the current level
void GameConfig::setCurrentLevel(const std::string& level) {
    if (!level.empty()) {
        currentLevel = level;
    }
    else {
        std::cerr << "Level name cannot be empty.\n";
    }
}

// Add score
void GameConfig::addScore(int points) {
    if (points > 0) {
        score += points;
    }
    else {
        std::cerr << "Score increment must be positive.\n";
    }
}

// Add a coin
void GameConfig::addCoin() {
    coins++;
}

// Set remaining time (seconds)
void GameConfig::setTimeLeft(int seconds) {
    if (seconds >= 0) {
        timeLeft = seconds;
    }
    else {
        std::cerr << "Time left cannot be negative.\n";
    }
}

// Update control mapping for a specific action
void GameConfig::updateControl(const std::string& action, sf::Keyboard::Key key) {
    if (controls.find(action) != controls.end()) {
        controls[action] = key;
    }
    else {
        std::cerr << "Action '" << action << "' not found in controls.\n";
    }
}

// Get the control key for a specific action
sf::Keyboard::Key GameConfig::getControl(const std::string& action) {
    if (controls.find(action) != controls.end()) {
        return controls[action];
    }
    else {
        std::cerr << "Action '" << action << "' not found in controls. Returning default key.\n";
        return sf::Keyboard::Unknown;
    }
}