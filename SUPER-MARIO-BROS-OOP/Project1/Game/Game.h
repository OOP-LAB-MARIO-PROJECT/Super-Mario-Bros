#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include "GameConfig.h" // global game configuration

#include <iostream>
#include <memory>

#include "../Utils/TextureManager.h"
#include "../Utils/SceneManager.h"
#include "../Utils/SoundManager.h"
#include "../Utils/FontManager.h"

#include "SceneList.h"

class Game {
private:
	
	sf::Clock m_clock;
	sf::RenderWindow* window = nullptr;
	
	TextureManager* textureManager = nullptr;
	SceneManager* sceneManager = nullptr;
	SoundManager* soundManager = nullptr;
	FontManager* fontManager = nullptr;
	bool m_isRunning = false;

public:

	static Game& getInstance() {
		static Game instance;
		return instance;
	}

	~Game();

	void start();
	void run();
	void exit();

	bool isRunning() const;

private:
	// private definition for singleton
	Game() = default;
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
};

