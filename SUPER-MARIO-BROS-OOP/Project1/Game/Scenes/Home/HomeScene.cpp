#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window) {
	Button startGame = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); }, "Start", 24, sf::Color::Black);
	buttons.push_back(startGame);
	
	Button exit = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }, "Exit", 24, sf::Color::Black); //thay exit bằng hàm thoát game
	buttons.push_back(exit);

	Button setting = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 400), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Setting); }, "Setting", 24, sf::Color::Black); //thay exit bằng hàm thoát game
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
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(getWindow());
	}
}

void HomeScene::update(float deltatime) {
	drawMenu();             // Draw buttons
	loopEvents();           // Handle events
}