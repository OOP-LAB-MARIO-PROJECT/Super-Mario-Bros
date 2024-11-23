
#include "Map.h"



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
	playerPos = { 0, 0 };
	playerPos = { 16, 16 };
	std::fstream fin(filename);

	if (fin.is_open())
		std::cout << "file opened\n";
	else
		std::cout << "file is not opened\n";

	int n, m;
	fin >> n >> m;

	sf::Vector2f pos(0, 0);
	std::cout << n << ' ' << m << '\n';

	m_row = n; m_col = m;

	const int size = 16;
	m_block_size = 16;

	tilesMap.reserve(n);
	tilesMap.resize(n);
	for (auto& row : tilesMap)
		row.reserve(m), row.resize(m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int t;
			fin >> t;

			tilesMap[i][j] = t;

			pos = { (float)j * size, (float)i * size };

			if (t == 1) {
				map.push_back(Tile(pos, { size, size }, false));
			}

			if (t == 2) { // coin
			//	props.push_back(std::make_unique<Coin>(Coin(pos, { size, size })));
			}

			if (t == 3) {
			//	breakableTiles.push_back(std::make_unique<MoveUpTile>(MoveUpTile(pos, { size, size }, false, player)));
			}

			if (t == 4) { // power up

			}

			if (t == 5) { // enemies

			}

			if (t == 7) { // test enemies
				//std::cout << "added test enemies\n";
				//myEntities.addEntity(std::make_unique<SimpleTestingEnemy>(SimpleTestingEnemy(pos, { size, size }, this)));
			}

			if (t == 9) { // groompa
				//std::make_unique<Entity>(Groompa(pos, { size, size }));
				//myEntities.addEntity(std::make_unique<Groompa>(Groompa(pos, { size, size }, this)));
			}
		}
	}

	fin.close();
}

std::vector <sf::RectangleShape> Map::getNearTiles(sf::Vector2f pos) {
	std::vector <sf::RectangleShape> tiles;
	for (Tile t : map) {
		sf::Vector2f p = t.getHitbox().getPosition();
		if (std::max(abs(pos.x - p.x), abs(pos.y - p.y)) <= 50)
			tiles.push_back(t.getHitbox());
	}

	//for (auto& t : breakableTiles) {
	//	sf::Vector2f p = t->getHitbox().getPosition();
	//	if (std::max(abs(pos.x - p.x), abs(pos.y - p.y)) <= 50) {
	//		tiles.push_back(t->getHitbox());
	//	}
	//}

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
	return tilesMap[y][x] != 0;
}
