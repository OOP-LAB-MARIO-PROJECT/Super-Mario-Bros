#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window) {
	if (!font.loadFromFile("Assets/Fonts/Roboto-Medium.ttf"))
	{
		std::cout << "Can't load font" << std::endl;
	}


	Button startGame = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); });
	buttons.push_back(startGame);
	Button exit = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }); //thay exit bằng hàm thoát game
	buttons.push_back(exit);

	options = { "Start", "Exit" };
	textPositions = { sf::Vector2f(300, 250), sf::Vector2f(300, 100) };
	buttonPositions = { sf::Vector2f(400, 250), sf::Vector2f(400, 350) };
	texts.resize(options.size());
	for (int i = 0; i < options.size(); i++)
	{
		texts[i].setFont(font);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(24);
		texts[i].setFillColor(sf::Color::Black);
		texts[i].setPosition(textPositions[i]);
	}
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

	for (int i = 0; i < texts.size(); i++)
	{
		getWindow()->draw(texts[i]);
	}
}

void HomeScene::update(float deltatime) {
	drawMenu();
	loopEvents();
}