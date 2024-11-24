#pragma once
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

#include "Tiles/Tile.h"
#include "Actors/Actor.h"
#include "Tiles/TileFactory.h"
#include "Actors/Player.h"

#include <vector>
#include <map>

class Player;

/*
Usefull fucntion need to note
	+# std::vector <Hitbox> getTiles();
	+# std::vector <Hitbox> getNearTiles(sf::Vector2f pos, bool gettrans = false);
	+# std::vector <Entity*> getNearEntity(Entity* en);
	+# sf::Vector2f getPlayerPos() const;
	+# sf::Vector2f getPlayerSize() const;
	+# sf::Vector2f getPlayerVel() const;
	+# bool isTileAt(sf::Vector2f pos) const;
	+# int getTileAt(sf::Vector2f pos) const;
	+# int getTileAt(std::pair <int, int> pos) const;
	+# std::pair <int, int> toMap(sf::Vector2f pos);
*/
class Map {
private:

	int m_row = 0;
	int m_col = 0;
	int m_block_size = 1;

	std::vector<Tile> map;
	std::map <std::pair <int, int>, int> tilePos;
	EntityManager myEntities;

	sf::Vector2f playerPos;
	sf::Vector2f playerSize;
	sf::Vector2f playerVel;

public:

	Map() {};
	~Map() {};

	void addTile(const Tile& tile);
	void render(sf::RenderWindow* window);
	void loadMap(const std::string& filename, Player* player);
	void resetPlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel);
	void update(float deltaTime, sf::Vector2f ppos, sf::Vector2f psize, sf::Vector2f pvel);
	
	
	// API for use
	// infomation for the actor to get
	std::vector <Hitbox> getTiles();
	std::vector <Hitbox> getNearTiles(sf::Vector2f pos, bool gettrans = false);
	std::vector <Entity*> getNearEntity(Entity* en);

	sf::Vector2f getPlayerPos() const;
	sf::Vector2f getPlayerSize() const;
	sf::Vector2f getPlayerVel() const;
	bool isTileAt(sf::Vector2f pos) const;

	int getTileAt(sf::Vector2f pos) const;

	// get by map tile set
	int getTileAt(std::pair <int, int> pos) const;
	// get near entity
		
	// to map coordinate
	std::pair <int, int> toMap(sf::Vector2f pos);

};

