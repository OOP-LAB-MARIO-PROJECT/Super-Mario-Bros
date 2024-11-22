#include "SoundManager.h"
#include <iostream>

bool SoundManager::addSound(const std::string& id, const std::string& filePath) {
    if (hasSound(id)) {
        std::cerr << "Sound with ID '" << id << "' already exists.\n";
        return false;
    }

    auto buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile(filePath)) {
        std::cerr << "Failed to load sound from: " << filePath << "\n";
        return false;
    }

    soundBuffers[id] = buffer;
    sf::Sound sound;
    sound.setBuffer(*buffer);
    sounds[id] = sound;
    return true;
}

void SoundManager::playSound(const std::string& id, bool loop) {
    if (!hasSound(id)) {
        std::cerr << "Sound with ID '" << id << "' not found.\n";
        return;
    }
    sounds[id].setLoop(loop);
    sounds[id].play();
}

void SoundManager::stopSound(const std::string& id) {
    if (!hasSound(id)) {
        std::cerr << "Sound with ID '" << id << "' not found.\n";
        return;
    }
    sounds[id].stop();
}

bool SoundManager::hasSound(const std::string& id) const {
    return sounds.find(id) != sounds.end();
}

void SoundManager::removeSound(const std::string& id) {
    if (!hasSound(id)) {
        std::cerr << "Sound with ID '" << id << "' not found.\n";
        return;
    }
    sounds.erase(id);
    soundBuffers.erase(id);
}