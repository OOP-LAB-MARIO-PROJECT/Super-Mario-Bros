#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window) {
	Button startGame = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "Start"; }, "Hehe", 24, sf::Color::White);
	buttons.push_back(startGame);
	
	Button exit = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }); //thay exit bằng hàm thoát game
	exit.setFont(font);
	exit.setText("Exit", 24, sf::Color::White);
	buttons.push_back(exit);
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
			//std::cout << "button " << i << '\n';
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