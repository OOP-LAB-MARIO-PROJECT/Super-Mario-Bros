
#include "Map.h"
#include "../../Utils/Tileset.h"


void Map::addTile(const Tile& tile) {
	map.push_back(tile);
};

void Map::render(sf::RenderWindow* window) {
	for (const Tile& t : map)
		t.render(window);

	myEntities.renderAll(window);
};

std::vector <sf::RectangleShape> Map::getTiles() {
	std::vector <sf::RectangleShape> ans;
	for (Tile& t : map) ans.push_back(t.getHitbox());
	return ans;
}

void Map::loadMap(const std::string& filename, Player* player) {
	Tileset mapLoader;
	std::map<std::string, std::vector <std::pair <int, int>>> myMapInfo = mapLoader.loadMapFromFile(filename);
	if (mapLoader.columns == 0) {
		throw std::exception("Devide by zero");
	}
	m_row = mapLoader.tilecount / mapLoader.columns;
	m_col = mapLoader.columns;
	m_block_size = mapLoader.tilewidth;

	sf::Vector2f size = sf::Vector2f{ (float)mapLoader.tilewidth, (float)mapLoader.tileheight };

	if (myMapInfo["player_pos"].size())
		player->setPos({ (float)myMapInfo["player_pos"][0].first, (float)myMapInfo["player_pos"][0].second });
	else {
		throw std::exception("No found player in map");
	}

	for (const auto& typeTile : myMapInfo) {
		for (const auto& tile : typeTile.second) {
			tilePos[toMap(sf::Vector2f{ (float)tile.first, (float)tile.second })] = map.size();
			addTile(TileFactory::createTile(typeTile.first, sf::Vector2f{(float)tile.first, (float)tile.second}, size));
		}
	}
}

std::vector <sf::RectangleShape> Map::getNearTiles(sf::Vector2f pos, bool gettrans) {
	std::vector <sf::RectangleShape> tiles;
	
	std::pair <int, int> currentPos = toMap(pos);// row and col
	
	for (int i = -2; i <= 2; i++) for (int j = -2; j <= 2; j++) {
		std::pair <int, int> newPos = currentPos;// row and col
		newPos.first += i;
		newPos.second += j;
		int id = getTileAt(newPos);
		if (id == -1) continue;
		if (!gettrans && map[id].isTrans())  continue;
		tiles.push_back(map[id].getHitbox());
	}

	return tiles;
}

void Map::update(float deltaTime, sf::Vector2f ppos, sf::Vector2f psize, sf::Vector2f pvel) {
	//std::vector <std::unique_ptr<Collectable>> newProps;
	//for (auto& p : props) {
	//	p->update(deltaTime);
	//	if (p->isCollideWithPlayer(playerPos, playerSize))
	//		p->applyEffect();
	//	else
	//		newProps.push_back(std::move(p));
	//}

	//props.clear();

	//for (auto& p : newProps)
	//	props.push_back(std::move(p));

	resetPlayer(ppos, psize, pvel);

	//for (auto& bt : breakableTiles) {
	//	bt->update(deltaTime);
	//}

	myEntities.updateAll(deltaTime);
}

void Map::resetPlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel) {
	playerPos = pos;
	playerSize = size;
	playerVel = vel;
}

sf::Vector2f Map::getPlayerPos() const {
	return playerPos;
}

sf::Vector2f Map::getPlayerSize() const {
	return playerSize;
}

sf::Vector2f Map::getPlayerVel() const {
	return playerVel;
}

bool Map::isTileAt(sf::Vector2f pos) const {
	int x = pos.x, y = pos.y;
	x /= m_block_size;
	y /= m_block_size;

	if (x >= m_col || y >= m_row) return false;
	return tilePos.count({ y, x });
}

int Map::getTileAt(sf::Vector2f pos) const {
	int x = pos.x, y = pos.y;
	x /= m_block_size;
	y /= m_block_size;

	if (x >= m_col || y >= m_row) return -1;
	if (!tilePos.count({ y, x })) return -1;

	return tilePos.find({ y, x })->second;
}

// at y, x coordinate
int Map::getTileAt(std::pair <int, int> pos) const {
	if (!tilePos.count(pos)) return -1;
	return tilePos.find(pos)->second;
}

std::pair <int, int> Map::toMap(sf::Vector2f pos) {
	int x = pos.x, y = pos.y;
	x /= m_block_size;
	y /= m_block_size;
	return { y, x };
}