#pragma once

#include "Tile.h"
#include <vector>
#include <string>
#include <vector>

namespace TILETYPE {

	static std::vector <std::string> normalPlatform = {
		"block1",
		"block2",
		"block3",
		"block4",
		"block-underground-1",
		"block-underground-2",
		"block-underground-3",
		"block-underground-4",
		"pipe-up-body-left",
		"pipe-up-body-right",
		"pipe-up-head-left",
		"pipe-up-head-right",
		"pipe-side-head-bottom",
		"pipe-side-head-up",
		"pipe-side-body-bottom",
		"pipe-side-body-up",
		"pipe-side-tail-up",
		"pipe-side-tail-bottom"
	};

	static std::vector <std::string> transparent = {
		"flag-1",
		"flag-2",
		"flag-3",
		"flag-4",
		"flag-body-1"
	};

	static bool isNormalPlatform(std::string name) {
		for (const auto& s : normalPlatform)
			if (s == name) return true;
		return false;
	}

	static bool isTransparent(std::string name) {
		for (const auto& s : transparent)
			if (s == name) return true;
		return false;
	}


}

class TileFactory {
public:
	static Tile createTile(const std::string& type, sf::Vector2f pos, sf::Vector2f size) {
		if (TILETYPE::isNormalPlatform(type)) {
			Tile ret(pos, size, false);
			ret.setTexture("tiles", type + "-0");
			ret.setRenderSprite(true);
			ret.setRenderHitbox(false);
			return ret;
		}
		if (TILETYPE::isTransparent(type)) {
			Tile ret(pos, size, true);
			ret.setTexture("tiles", type + "-0");
			ret.setRenderSprite(true);
			ret.setRenderHitbox(false);
			return ret;
		}

		return 	Tile(pos, size);
	}
};

