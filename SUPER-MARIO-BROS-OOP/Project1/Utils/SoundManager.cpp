#include "SoundManager.h"
#include <iostream>
#include <fstream>

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

    sounds[id].setVolume(volume);
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

void SoundManager::loadFromInterface(const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Cannot open interface " + filename << '\n';
        return;
    }

    std::string soundName, soundFile;
    while (fin >> soundName) {
        if (!(fin >> soundFile)) {
            std::cerr << "Missing sound " + soundName << '\n';
            return;
        }

        soundFile = "Assets/Sounds/" + soundFile;
        addSound(soundName, soundFile);
    }

    std::cout << "Loaded sound successully";

    fin.close();
}

void SoundManager::updateVolume(float vol) {
    
    for (auto& mySound : sounds) {
        if (mySound.second.getStatus() == sf::Sound::Playing) {
            auto offset = mySound.second.getPlayingOffset();
            mySound.second.stop();
            mySound.second.setVolume(vol);
            mySound.second.setPlayingOffset(offset);
            mySound.second.play();
        }
    }
    
    volume = vol;
}

float SoundManager::getVolume() const {
    return volume;
}