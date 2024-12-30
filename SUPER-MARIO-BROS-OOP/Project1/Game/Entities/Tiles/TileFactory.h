#pragma once

#include "Tile.h"
#include "MoveUpTile.h"
#include "QuestionTile.h"
#include "PipeHead.h"
#include "MovingPlatform.h"
#include "RotateFire.h"
#include "BossHammer.h"
#include "Brigde.h"
#include "Flag.h"

#include <vector>
#include <string>
#include <vector>

namespace TILETYPE {

	static std::vector <std::string> normalPlatform = {
		"block1",
		"block2",
		"block3",
		"block4",
		"block5",
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
		"block_grass_1",
		"block_grass_2",
		"block_grass_3",
		"block_rock",
		"stair",
		"block_green",

	};

	static std::vector <std::string> pipeHead = {
		"pipe-up-head-left",
		"pipe-up-head-right",
		"pipe-up-head-left-light",
		"pipe-up-head-right-light",
		"pipe-side-head-bottom",
		"pipe-side-head-up"
	};

	static std::vector <std::string> interactable = {
		"block2",
		"block-underground-3",
		"question",
		"hammer",
		"bridge",
		"flag"
	};

	static std::vector <std::string> transparent = {
		"flag-1",
		"flag-2",
		"flag-3",
		"flag-4",
		"flag-dark-1",
		"flag-body-1",
		"flag-body-light-1",
		"castle1",
		"castle2",
		"castle3",
		"castle-arch",
		"castle-window-right",
		"castle-window-left",
		"cloud1",
		"cloud2",
		"cloud3",
		"cloud4",
		"cloud5",
		"cloud6",
		"soil",
		"trunk",
		"bunch",
		"bunch_up",
		"bunch_down",
		"bunch_light",
		"bunch_up_light",
		"bunch_down_light",
		"fence",
		"moss",
		"edge_moutain_left",
		"edge_moutain_right",
		"body_moutain",
		"body_moutain_right",
		"body_moutain_left",
		"top_mountain",
		"grass1",
		"grass2",
		"grass3",
		"handrail",
		"handrail_light",
		"water_surface_2",
		"water",
		"water2",
		"lavar1",
		"lavar2",
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

