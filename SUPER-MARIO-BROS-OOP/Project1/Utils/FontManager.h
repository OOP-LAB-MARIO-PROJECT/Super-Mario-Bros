#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <memory>

class FontManager {
public:
    
    FontManager(const FontManager&) = delete;
    FontManager& operator=(const FontManager&) = delete;

    // Singleton instance
    static FontManager& getInstance() {
        static FontManager instance;
        return instance;
    }

    void loadFromInterface(const std::string& fileName);


    bool addFont(const std::string& id, const std::string& filePath);


    
    std::shared_ptr<sf::Font> getFont(const std::string& id) const;

  
    bool hasFont(const std::string& id) const;

    
    void removeFont(const std::string& id);

private:
    FontManager() = default; 
    ~FontManager() = default;

    std::unordered_map<std::string, std::shared_ptr<sf::Font>> fonts;  
};
