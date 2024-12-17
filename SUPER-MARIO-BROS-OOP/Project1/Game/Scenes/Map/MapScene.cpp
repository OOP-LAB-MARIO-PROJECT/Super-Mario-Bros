#include "MapScene.h"
MapScene::MapScene(sf::RenderWindow* window) : Scene(window)
{
	gameConfig = &GameConfig::getInstance();
	//for map selection
	const std::string& list = "Assets/Map/map_interface.txt";
	std::ifstream fin(list);
	if (!fin.is_open()) {
		throw std::exception("Cannot open list\n");
	}
	std::string mapName, mapPath;
	while (fin >> mapName >> mapPath) {
		gameConfig->mapList[mapName] = mapPath;
		std::cout << "Map loaded: " << mapName << ' ' << mapPath << '\n';
	}
	
	int i = 0;
	for (auto it : gameConfig->mapList)
	{
		allMapNames.push_back(it.first);
		++i;
	}

	int j = 0;
	for (auto it : gameConfig->unlockedLevel)
	{
		unlockedMapNames.push_back(it.first);
	}
	//đề đây mai làm tiếp, thêm mấy cái box vô để tên các map và rồi check coi những map nào là unlocked thì màu khác những cái đã unlock là màu khác
	//rồi cứ handle thôi
}

//std::string MapScene::getMapName()
//{ 
//
//}
void MapScene::drawScene()
{

}
void  MapScene::loopEvents()
{

}

void MapScene::update(float deltatime)
{ 

}
