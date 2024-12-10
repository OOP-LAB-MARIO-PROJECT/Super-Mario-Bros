#pragma once
#include <SFML/Graphics.hpp>

#include "Actors/Player.h"
#include "Tiles/TileFactory.h"
#include "EntityFactory.h"
#include "../../Utils/EntityManager.h"
#include "../../Utils/QuadTree.h"

#include <vector>
#include <map>

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
	Hitbox renderSpace;


	std::vector<Tile*> map;
	std::vector<Tile*> tempMap;
	std::map <std::pair <int, int>, int> tilePos;
	
	QuadTree quadMap;


	Player* player = NULL;
	sf::Vector2f playerPos;
	sf::Vector2f playerSize;
	sf::Vector2f playerVel;
	
	int playerMode = 0;
public:

	Map() {
		quadMap.init(1e4, 600, 20);
	};
	~Map();

	void updateEnvironment();
	void addTile(Tile* tile);
	void render(sf::RenderWindow* window);
	void loadMap(const std::string& filename, Player* player);
	void resetPlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel, int mode);
	void update(float deltaTime, sf::Vector2f ppos, sf::Vector2f psize, sf::Vector2f pvel, int mode);
	void setRenderSpace(sf::Vector2f pos, sf::Vector2f size);
	
	// API for use
	// infomation for the actor to get
	std::vector <Hitbox> getTiles();
	std::vector <Hitbox> getNearTiles(sf::Vector2f pos, bool gettrans = false);
	std::vector <Entity*> getNearPointerTiles(sf::Vector2f pos, bool gettrans = false);
	std::vector <Entity*> getNearEntity(Entity* en);

	sf::Vector2f getPlayerPos() const;
	sf::Vector2f getPlayerSize() const;
	sf::Vector2f getPlayerVel() const;
	int getPlayerMode() const;
	bool isTileAt(sf::Vector2f pos) const;

	int getTileAt(sf::Vector2f pos) const;

	// get by map tile set
	int getTileAt(std::pair <int, int> pos) const;
	// get near entity
		
	// to map coordinate
	std::pair <int, int> toMap(sf::Vector2f pos);
};


