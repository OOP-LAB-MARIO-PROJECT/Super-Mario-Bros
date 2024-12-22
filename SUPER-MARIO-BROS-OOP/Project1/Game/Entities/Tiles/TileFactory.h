#pragma once

#include "Tile.h"
#include "MoveUpTile.h"
#include "QuestionTile.h"
#include "PipeHead.h"
#include "MovingPlatform.h"
#include "RotateFire.h"

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
		"block-underground-3",
		"block-underground-4",
		"block-underground-5",
		"pipe-up-body-left",
		"pipe-up-body-right",
		"pipe-up-body-left-light",
		"pipe-up-body-right-light",
		"pipe-side-body-bottom",
		"pipe-side-body-up",
		"pipe-side-tail-up",
		"pipe-side-tail-bottom",
		"cloud1",
		"cloud2",
		"cloud3",
		"cloud4",
		"cloud5",
		"cloud6",
		"block-grass-1",
		"block-grass-2",
		"block-grass-3"
		"soil",
		"block-rock",
		"bridge",
		"block_green"
	};

	static std::vector <std::string> comeAccross = {
		"bunch",
		"bunch_up",
		"bunch_down",
		"bunch_up_light",
		"bunch_down_light",
		"bunch_light",
		"trunk",
		"fence",
		"moss",
		"edge_mountain_left",
		"top_mountain",
		"edge_mountain_right",
		"body_mountain",
		"handrail",
	};

	static std::vector <std::string> pipeHead = {
		"pipe-up-head-left",
		"pipe-up-head-right",
		"pipe-side-head-bottom",
		"pipe-side-head-up",
		"pipe-up-head-left-light",
		"pipe-up-head-right-light",
	};

	static std::vector <std::string> interactable = {
		"block2",
		"block-underground-3",
		"question"
		"hammer",
		"horizontal_wire",
		"vertical_wire",
		"pulley_left",
		"pulley_right"
	};

	static std::vector <std::string> transparent = {
		"flag-1",
		"flag-2",
		"flag-3",
		"flag-4",
		"flag-body-1",
		"castle1",
		"castle2",
		"castle3",
		"castle-arch",
		"castle-window-right",
		"castle-window-left"
	};

	static bool isNormalPlatform(std::string name) {
		for (const auto& s : normalPlatform)
			if (s == name) return true;
		return false;
	}

	static bool isInteractable(std::string name) {
		return std::find(interactable.begin(), interactable.end(), name) != interactable.end();
	}


	static bool isPipeHead(std::string name) {
		return std::find(pipeHead.begin(), pipeHead.end(), name) != pipeHead.end();
	}

	static bool isTransparent(std::string name) {
		for (const auto& s : transparent)
			if (s == name) return true;
		return false;
	}


}

class TileFactory {

	static std::string findProperties(std::string& s);

public:
	static Tile* createTile(std::string type, sf::Vector2f pos, sf::Vector2f size);
};

