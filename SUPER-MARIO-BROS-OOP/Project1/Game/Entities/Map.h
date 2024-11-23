#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

#include "Tiles/Tile.h"
#include "Actors/Actor.h"

#include <vector>
#include <map>

class Player;

class Map {
private:

	int m_row = 0;
	int m_col = 0;
	int m_block_size = 1;

	std::vector<std::vector<short>> tilesMap;
	std::vector<Tile> map;

	EntityManager myEntities;

	sf::Vector2f playerPos;
	sf::Vector2f playerSize;
	sf::Vector2f playerVel;

public:

	Map() {};
	~Map() {};

	void addTile(const Tile& tile);
	void render(sf::RenderWindow* window);

	std::vector <sf::RectangleShape> getTiles();
	std::vector <sf::RectangleShape> getNearTiles(sf::Vector2f pos);

	void loadMap(const std::string& filename, Player* player);
	void resetPlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel);
	void update(float deltaTime, sf::Vector2f ppos, sf::Vector2f psize, sf::Vector2f pvel);

	// infomation for the actor to get
	sf::Vector2f getPlayerPos() const;
	sf::Vector2f getPlayerSize() const;
	sf::Vector2f getPlayerVel() const;
	bool isTileAt(sf::Vector2f pos) const;

};

