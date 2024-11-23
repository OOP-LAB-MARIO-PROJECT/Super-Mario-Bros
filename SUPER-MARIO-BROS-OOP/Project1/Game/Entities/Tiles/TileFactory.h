#pragma once

#include "Tile.h"
#include <vector>
#include <string>


class TileFactory {
public:
	static Tile createTile(const std::string& type, sf::Vector2f pos, sf::Vector2f size){
		if (type == "block1") {
			return 	Tile(pos, size);
			
		}

		return 	Tile(pos, size);
	}
};

