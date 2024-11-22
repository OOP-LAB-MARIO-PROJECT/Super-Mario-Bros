#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include "Tileset.h"

/* 
=====================================
Flyweight - pattern

Support:
	- void loadNewTexture(const std::string& filename, const std::string& textureName);

	- void setTextureRect(sf::Sprite& sprite, const std::string& sourceName, const std::string& rectName);


====================================== 
*/
class TextureManager {
private:
	std::map <std::string, sf::Texture> myTexture;
	std::map <std::string, std::map<std::string, std::pair <std::pair<int, int>, std::pair <int, int>>>> textureRect;

public:

	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager& getInstance() {
		static TextureManager instance; // Guaranteed to be lazy-initialized and thread-safe
		return instance;
	}

	// load new texture from file -> the texture should be **2 FILE**, the tilemap file with extension .tsx and a picture denote the texture that suitable for the tilemap file
	void loadNewTexture(const std::string& filename, const std::string& textureName);

	// set the rectange texture for a sprite -> the texture that will be render
	void setTextureRect(sf::Sprite& sprite, const std::string& sourceName, const std::string& rectName);

	void loadFromInterface(const std::string& filename);

private:
	TextureManager() = default; // Private constructor
	~TextureManager() = default;
};

