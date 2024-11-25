#pragma once
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class SoundManager {
public:


    SoundManager(const SoundManager&) = delete;
    SoundManager& operator=(const SoundManager&) = delete;

    static SoundManager& getInstance() {
        static SoundManager instance; 
        return instance;
    }

    bool addSound(const std::string& id, const std::string& filePath);
    void playSound(const std::string& id, bool loop = false);
    void stopSound(const std::string& id);
    bool hasSound(const std::string& id) const;
    void removeSound(const std::string& id);
    
    void loadFromInterface(const std::string& filename);


private:
    SoundManager() = default; // Private constructor
    ~SoundManager() = default;

    std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
    std::unordered_map<std::string, sf::Sound> sounds;
};