#include "FontManager.h"
#include <iostream>
#include <fstream>


void FontManager::loadFromInterface(const std::string& filename) {
    std::ifstream file(filename);  
    if (!file.is_open()) {
        std::cout << "Can not open file interface: " << filename << "\n";
        return;
    }

    std::string fontID, fontPath;
    while (file >> fontID >> fontPath) {
        fontPath = "Assets/Fonts/" + fontPath;
        if (!addFont(fontID, fontPath)) {
            std::cerr << "Can not add font with ID: " << fontID << "\n";
        }
    }
    std::cout << "Loaded font successully";
    file.close();
}


bool FontManager::addFont(const std::string& id, const std::string& filePath) {
    if (hasFont(id)) {
        std::cerr << "Font with ID '" << id << "' already exsits.\n";
        return false;
    }

    auto font = std::make_shared<sf::Font>();
    if (!font->loadFromFile(filePath)) {
        std::cerr << "Can not load font from: " << filePath << "\n";
        return false;
    }

    fonts[id] = font; 
    return true;
}


std::shared_ptr<sf::Font> FontManager::getFont(const std::string& id) const {
    auto it = fonts.find(id);
    if (it != fonts.end()) {
        std::cout << "font is found";
        return it->second;
        
    }
    return nullptr;  
}


bool FontManager::hasFont(const std::string& id) const {
    return fonts.find(id) != fonts.end();
}


void FontManager::removeFont(const std::string& id) {
    if (!hasFont(id)) {
        std::cerr << "Can not find font '" << id << "'.\n";
        return;
    }
    fonts.erase(id);
}