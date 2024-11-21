#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>
#include "Tileset.h"

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

	void loadNewTexture(const std::string& filename, const std::string& textureName);
	void setTextureRect(sf::Sprite& sprite, const std::string& sourceName, const std::string& rectName);

private:
	TextureManager() = default; // Private constructor
	~TextureManager() = default;
};

