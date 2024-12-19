#include "MapScene.h"
MapScene::MapScene(sf::RenderWindow* window) : Scene(window)
{
	gameConfig = &GameConfig::getInstance();
	//load all map names from the txt file into mapList of gameConfig
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
	fin.close();


	//all map names
	for (auto it : gameConfig->mapList) {
		allMapNames[it.first] = false; //false means locked
	}

	Button map11 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(100, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-1";  }, "map 1-1", 20, sf::Color::Black);
	buttons.push_back(map11);

	Button map12 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(100, 300), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() { 
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-2"; }, "map 1-2", 20, sf::Color::Black);
	buttons.push_back(map12);

	Button map13 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(100, 500), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-3"; }, "map 1-3", 20, sf::Color::Black);
	buttons.push_back(map13);

	Button map21 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(400, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-1"; }, "map 2-1", 20, sf::Color::Black);
	buttons.push_back(map21);

	Button map22 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(400, 300), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-2"; }, "map 2-2", 20, sf::Color::Black);
	buttons.push_back(map22);

	Button map23 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(400, 500), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-3"; }, "map 2-3", 20, sf::Color::Black);
	buttons.push_back(map23);

	Button map31 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(700, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-1"; }, "map 3-1", 20, sf::Color::Black);
	buttons.push_back(map31);

	Button map32 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(700, 300), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-2"; }, "map 3-2", 20, sf::Color::Black);
	buttons.push_back(map32);

	Button map33 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(700, 500), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-3"; }, "map 3-3", 20, sf::Color::Black);
	buttons.push_back(map33);

	Button play = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(100, 700), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); }, "Play", 17, sf::Color::Black);
	buttons.push_back(play);
}

void MapScene::drawScene()
{
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(getWindow());
	}
	for (int i = 0; i < texts.size(); ++i)
	{
		getWindow()->draw(texts[i]);
	}
}

bool MapScene::isUnlocked(std::string mapName) {
	return gameConfig->unlockedLevel.find(mapName) != gameConfig->unlockedLevel.end();
}

void  MapScene::loopEvents()
{
	sf::Event event;
	while (getWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
		for (int i = 0; i < buttons.size(); ++i)
		{
			std::cout << "num of buttons: " << buttons.size() << '\n';
			std::cout << disabled[i] << '\n';
			if (disabled[i] == true)
			{
				buttons[i].handleEvent(event, *getWindow());
			}
		}
	}
}

void MapScene::update(float deltatime)
{ 
	for (auto it : allMapNames)
	{
		disabled.push_back(isUnlocked(it.first));
	}
	disabled.push_back(true);
	drawScene();
	loopEvents();

}
