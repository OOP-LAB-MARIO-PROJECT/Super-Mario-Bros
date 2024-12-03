
#include "Map.h"
#include "../../Utils/Tileset.h"

Map::~Map() {
	for (auto x : map) delete x;
}

void Map::addTile(Tile* tile) {
	quadMap.insert((Entity*)tile);
	map.push_back(tile);
};

void Map::render(sf::RenderWindow* window) {
	EntityManager::getInstance().renderAll(window);
	for (Tile* t : map)
		t->render(window);
};

std::vector <Hitbox> Map::getTiles() {
	std::vector <Hitbox> ans;
	for (Tile* t : map) ans.push_back(t->getHitbox());
	return ans;
}

void Map::loadMap(const std::string& filename, Player* player) {
	this->player = player;
	Tileset mapLoader;
	std::map<std::string, std::vector <std::pair <int, int>>> myMapInfo = mapLoader.loadMapFromFile(filename);
	if (mapLoader.columns == 0) {
		throw std::exception("Devide by zero");
	}
	m_row = mapLoader.tilecount / mapLoader.columns;
	m_col = mapLoader.columns;
	m_block_size = mapLoader.tilewidth;

	quadMap.init(m_col * (m_block_size + 10), m_row * (m_block_size + 10), 20);
	EntityManager::getInstance().setSpace(m_col * (m_block_size + 10), m_row * (m_block_size + 10));

	sf::Vector2f size = sf::Vector2f{ (float)mapLoader.tilewidth, (float)mapLoader.tileheight };

	if (myMapInfo["player_pos"].size()) {
		player->setPos({ (float)myMapInfo["player_pos"][0].first, (float)myMapInfo["player_pos"][0].second });
		resetPlayer(player->getPos(), player->getSize(), player->getVel(), player->currentMode);
	}
	else {
		throw std::exception("No found player in map");
	}

	EntityFactory enFactory;

	for (const auto& typeTile : myMapInfo) {

		if (FACTORY_ENTITY_TYPE::isEntityNotTile(typeTile.first)) {
			for (const auto& tile : typeTile.second) {
				EntityManager::getInstance().
					addEntity(enFactory.createEntity(typeTile.first, sf::Vector2f{ (float)tile.first, (float)tile.second }, size));
			}
			continue;
		}

		for (const auto& tile : typeTile.second) {
			Tile* tmp = TileFactory::createTile(typeTile.first, sf::Vector2f{ (float)tile.first, (float)tile.second }, size);
		
			addTile(tmp);
		}
	}
}

std::vector <Hitbox> Map::getNearTiles(sf::Vector2f pos, bool gettrans) {
	std::vector <Hitbox> tiles;
	std::vector <Hitbox> tmp;
	
	Hitbox space = {
		pos - sf::Vector2f(32, 32),
		sf::Vector2f(64, 64)
	};

	std::vector <Entity*> nearTile = quadMap.nearEntity(space);
	for (auto x : nearTile) {
		if (x->getType() == TRANS && !gettrans) continue;
		tmp.push_back(x->getHitbox());
	}
	return tmp;
}

void Map::update(float deltaTime, sf::Vector2f ppos, sf::Vector2f psize, sf::Vector2f pvel, int mode) {

	std::vector <Tile*> alive;
	for (auto t : map) if (!t->isDead()) {
		alive.push_back(t);
		//if (t->getType() >> MOVING_TILE & 1) std::cout << "i updated you\n";
		t->update(deltaTime);
		//if (t->getType() >> MOVING_TILE & 1) std::cout << "i done updated you\n";
		t->notify(t);
	}
	map = alive;

	quadMap.checkForPending();

	resetPlayer(ppos, psize, pvel, mode);
}

void Map::resetPlayer(sf::Vector2f pos, sf::Vector2f size, sf::Vector2f vel, int mode) {
	playerPos = pos;
	playerSize = size;
	playerVel = vel;
	playerMode = mode;
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

int Map::getPlayerMode() const{
	return playerMode;
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

std::vector <Entity*> Map::getNearEntity(Entity* en) {
	return 	EntityManager::getInstance().getNearEntity(en);
}

std::vector <Entity*> Map::getNearPointerTiles(sf::Vector2f pos, bool gettrans) {

	Hitbox space = {
		pos - sf::Vector2f(32, 32),
		sf::Vector2f(64, 64)
	};

	std::vector <Entity*> nearTile = quadMap.nearEntity(space);
	std::vector <Entity*> tiles;
	for (auto x : nearTile) {
		if (x->getType() == TRANS && !gettrans) continue;
		tiles.push_back(x);
	}
	return tiles;
}

void Map::updateEnvironment() {
	player->updateEvironment(
		getNearTiles(player->getPos()),
		EntityManager::getInstance().
		getNearEntity(player)
	);

	player->nearPointerTiles = getNearPointerTiles(player->getPos());

	std::vector<Entity*>& entities = EntityManager::getInstance().
		getEntities();
	for (auto en : entities) {
		std::vector <Hitbox> neartile = getNearTiles(en->getHitbox().pos);
		std::vector <Entity*> nearptr = getNearPointerTiles(en->getHitbox().pos);
		for (auto x : nearptr) neartile.push_back(x->getHitbox());

		en->updateEvironment(
			neartile,
			EntityManager::getInstance().
			getNearEntity(en)
		);
		en->otherEntities.push_back(player);
	}
}