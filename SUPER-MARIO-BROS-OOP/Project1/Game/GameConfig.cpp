#include "GameConfig.h"
#include <fstream>
#include <iostream>
using json = nlohmann::json;
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
        std::cout << "cur lev" << ' ' << level << '\n';
    }
    else {
        std::cerr << "Level name cannot be empty.\n";
    }
}


void GameConfig::setNextLevel(const std::string& level) {
    if (!level.empty()) {
        nextLevel = level;
        std::cout << "next lev" << ' ' << level << '\n';
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
	//	oldKey = controls[action];
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


// Save & Load
void GameConfig::saveToFile(const std::string& filename) {
    json j;
    
    // Meta data
    j["volume"] = volume;
    j["playerName"] = playerName;
    
    // Lưu controls
    for (const auto& pair : controls) {
        j["controls"][pair.first] = pair.second;
    }

    j["unlocked-level"] = unlockedLevel;

    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4); // Định dạng JSON đẹp mắt
        file.close();
    }
    else {
        std::cerr << "Unable to open file for saving: " << filename << std::endl;
    }

    file.close();
}

void GameConfig::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        json j;
        file >> j;
        file.close();

        volume = j["volume"];
        playerName = j["playerName"];
        currentLevel = j["currentLevel"];
        unlockedLevel = j["unlocked-level"];
        
        // Tải controls
        for (auto& pair : controls) {
            if (j["controls"].contains(pair.first)) {
                pair.second = j["controls"][pair.first];
            }
        }
    }
    else {
        std::cerr << "Unable to open file for loading: " << filename << std::endl;
        std::cerr << "New player: " << playerName << std::endl;
    }
}


void GameConfig::saveLevel() {
    if (unlockedLevel.find(currentLevel) == unlockedLevel.end()) {
        unlockedLevel[currentLevel] = { score, coins};
    }
    else {
        std::pair <int, int> newRecord = { score, coins };
        unlockedLevel[currentLevel] = std::max(newRecord, unlockedLevel[currentLevel]);
    }
}

void GameConfig::saveToFile() {
    std::string filename = "Users/" + playerName + ".json";
    saveToFile(filename);
}

void GameConfig::loadFromFile() {
    std::string filename = "Users/" + playerName + ".json";
    loadFromFile(filename);
}