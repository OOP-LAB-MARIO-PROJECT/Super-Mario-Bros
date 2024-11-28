#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window) {
	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;
	sf::Vector2f midCoordinate(midScreenX - 100, midScreenY - 50);
	Button startGame = Button::createButton(sf::Vector2f(200, 100), midCoordinate, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); }, "start", 20, sf::Color::Black);
	buttons.push_back(startGame);
	
	Button exit = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(midCoordinate.x, midCoordinate.y - 200), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }, "exit", 20, sf::Color::Black); //thay exit bằng hàm thoát game
	buttons.push_back(exit);

	Button setting = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(midCoordinate.x, midCoordinate.y + 210), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Setting); }, "setting", 15, sf::Color::Black); //thay exit bằng hàm thoát game
	buttons.push_back(setting);
}


void HomeScene::loopEvents()
{
	sf::Event event;
	while (getWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].handleEvent(event, *getWindow());
		}
	}
}


void HomeScene::drawMenu()
{
	getWindow()->clear(sf::Color::Color(107, 137, 253));
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(getWindow());
		std::cout << "draw option" << i + 1;
	}
	//std::cout << "total options: " << buttons.size() << '\n';
}

void HomeScene::update(float deltatime) {
	drawMenu();             // Draw buttons
	loopEvents();           // Handle events
}