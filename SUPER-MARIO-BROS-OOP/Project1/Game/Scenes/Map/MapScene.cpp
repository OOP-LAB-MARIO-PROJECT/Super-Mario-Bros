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

	gameConfig->hasMapSelection = false;
	gameConfig->chosenMap = "map-1-1";
	gameConfig->levelStatus = FIRST_START;

	sf::Color color = sf::Color::Color(251, 188, 174);
	Button map11 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(80, 310), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-1";  }, "map 1-1", 15, color, "UI_Components/UI_Texture_Pack/world1-1.png");
	buttons.push_back(map11);

	Button map12 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(195, 345), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() { 
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-2";
		}, "map 1-2", 15, color,"UI_Components/UI_Texture_Pack/world1-2.png");
	buttons.push_back(map12);

	Button map13 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(325, 340), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-3"; }, "map 1-3", 15, color, "UI_Components/UI_Texture_Pack/world1-3.png");
	buttons.push_back(map13);
	
	Button map14 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(480, 340), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-1-4"; }, "map 1-4", 15, color, "UI_Components/UI_Texture_Pack/world1-4.png");
	buttons.push_back(map14);

	Button map21 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(610, 245), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-1"; }, "map 2-1", 15, color, "UI_Components/UI_Texture_Pack/world2-1.png");
	buttons.push_back(map21);

	Button map22 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(725, 165), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-2"; }, "map 2-2", 15, color, "UI_Components/UI_Texture_Pack/world2-2.png");
	buttons.push_back(map22);

	Button map23 = Button::createButton(sf::Vector2f(60, 120), sf::Vector2f(885, 185), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-3"; }, "map 2-3", 15, color, "UI_Components/UI_Texture_Pack/world2-3.png");
	buttons.push_back(map23);

	Button map24 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(735, 245), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-2-4";  }, "map 2-4", 15, color, "UI_Components/UI_Texture_Pack/world2-4.png");
	buttons.push_back(map24);

	Button map31 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(830, 300), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-1"; }, "map 3-1", 15, color, "UI_Components/UI_Texture_Pack/world3-1.png");
	buttons.push_back(map31);

	Button map32 = Button::createButton(sf::Vector2f(50, 105), sf::Vector2f(770, 460), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-2"; }, "map 3-2", 15, color, "UI_Components/UI_Texture_Pack/world3-2.png");
	buttons.push_back(map32);

	Button map33 = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(910, 365), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-3"; }, "map 3-3", 15, color, "UI_Components/UI_Texture_Pack/world3-3.png");
	buttons.push_back(map33);

	Button map34 = Button::createButton(sf::Vector2f(60, 60), sf::Vector2f(1110, 230), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() {
			gameConfig->hasMapSelection = true;
			gameConfig->chosenMap = "map-3-4"; }, "map 3-4", 15, color, "UI_Components/UI_Texture_Pack/world3-4.png");
	buttons.push_back(map34);
}

std::vector<std::string> MapScene::reformat(){
	std::vector<std::string> unlockedMapNames;
	for (auto it : this->unlockedMapNames)
	{
		it[3] = ' ';
		unlockedMapNames.push_back(it);

	}
	return unlockedMapNames;
}

void MapScene::drawScene()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/MapScene.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.75, 1.5);
	getWindow()->draw(backgroundSprite);
	std::shared_ptr<sf::Font> font = FontManager::getInstance().getFont("Mario");
	sf::Text text;
	text.setFont(*font);
	text.setCharacterSize(20);
	text.setString("Current level: " + reformat().back());
	text.setFillColor(sf::Color::White);
	text.setPosition(100, 100);
	getWindow()->draw(text);
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
			//std::cout << "num of buttons: " << buttons.size() << '\n';
			//std::cout << disabled[i] << '\n';
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
		if (isUnlocked(it.first))
		{
			unlockedMapNames.push_back(it.first);
		}
	}
	drawScene();
	loopEvents();

	if (gameConfig->hasMapSelection) {
		gameConfig->setCurrentLevel(gameConfig->chosenMap);
		SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game);
	}
}
