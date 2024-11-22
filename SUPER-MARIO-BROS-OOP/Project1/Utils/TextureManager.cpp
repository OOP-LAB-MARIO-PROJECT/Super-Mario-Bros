#include "TextureManager.h"
#include <iostream>
#include <fstream>

void TextureManager::loadNewTexture(const std::string& filename, const std::string& textureName) {
	Tileset tileset;
	tileset.loadFile(filename);
	if (myTexture[tileset.name].loadFromFile(textureName))
		std::cout << "successfully loaded texture " + textureName << '\n';
	for (const auto& pii : tileset.mp)
		textureRect[tileset.name][pii.first] = { pii.second , {tileset.tilewidth, tileset.tileheight} };

	std::cout << "Loaded " << filename << " with texture " << textureName << " successfully " << "with " << textureRect.size() << " tiles, using name of " << tileset.name << ' ' << "rect-name\n";
}

void TextureManager::setTextureRect(sf::Sprite& sprite, const std::string& textureName, const std::string& rectName) {

	if (sprite.getTexture() != &myTexture[textureName])
		sprite.setTexture(myTexture[textureName]);

	if (!textureRect.count(textureName)) {
		std::cout << "Cannot find texture with name " + textureName << '\n';
		return;
	}

	if (!textureRect[textureName].count(rectName)) {
		std::cout << "Cannot find texture rect with name " + rectName << '\n';
		return;

	}

	auto rec = textureRect[textureName][rectName];
	std::cout << "set render texture at " << rec.first.first << ' ' << rec.first.second << '\n';
	sf::IntRect rect(rec.first.first, rec.first.second, rec.second.first, rec.second.second);
	sprite.setTextureRect(rect);
	std::cout << "texture pos" << (int)sprite.getTexture() << '\n';
}


void TextureManager::loadFromInterface(const std::string& filename) {
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		std::cerr << "Cannot open interface " + filename << '\n';
		return;
	}

	std::string tileName, textureName;
	while (fin >> tileName) {
		if (!(fin >> textureName)) {
			std::cerr << "Missing texture " + tileName << '\n';
			return;
		}

		tileName = "Assets/Textures/" + tileName;
		textureName = "Assets/Textures/" + textureName;
		loadNewTexture(tileName, textureName);
	}
	
	std::cerr << "Loaded texture successfully" << '\n';

	fin.close();
}
