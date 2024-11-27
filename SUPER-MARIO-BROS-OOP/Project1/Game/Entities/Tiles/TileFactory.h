#pragma once

#include "Tile.h"
#include "MoveUpTile.h"
#include "QuestionTile.h"

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


	static std::vector <std::string> interactable = {
		"block2",
		"block-underground-2",
		"question"
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

	static bool isInteractable(std::string name) {
		return std::find(interactable.begin(), interactable.end(), name) != interactable.end();
	}

	static bool isTransparent(std::string name) {
		for (const auto& s : transparent)
			if (s == name) return true;
		return false;
	}


}

class TileFactory {
public:
	static Tile* createTile(const std::string& type, sf::Vector2f pos, sf::Vector2f size) {

		if (TILETYPE::isInteractable(type)) {
			if (type == "question") {
				Tile* r = new QuestionTile(pos, size, false);
				//r->setTexture("tiles", type + "-0");
				r->setRenderSprite(true);
				r->setRenderHitbox(false);
				return r;
			}

			Tile* r = new MoveUpTile(pos, size, false);
			r->setTexture("tiles", type + "-0");
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}
		
		if (TILETYPE::isNormalPlatform(type)) {
			Tile* r = new Tile(pos, size, false);
			r->setTexture("tiles", type + "-0");
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}

		if (TILETYPE::isTransparent(type)) {
			Tile* r = new Tile(pos, size, true);
			r->setTexture("tiles", type + "-0");
			r->setRenderSprite(true);
			r->setRenderHitbox(false);
			return r;
		}

		return new Tile(pos, size);
	}
};

