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

	idleMarioTexture.loadFromFile("UI_Components/UI_Texture_Pack/IdleMario.png");
	idleMario.setTexture(idleMarioTexture);

	sf::FloatRect idleMarioCoord = idleMario.getGlobalBounds();
	sf::Vector2u windowCoord = getWindow()->getSize();

	float bottomRightX = windowCoord.x - idleMarioCoord.width;
	float bottomRightY = windowCoord.y - idleMarioCoord.height;
	idleMario.setPosition(bottomRightX, bottomRightY);
	getWindow()->draw(idleMario);

	hoveredMarioTexture.loadFromFile("UI_Components/UI_Texture_Pack/HoveredMario.png");
	hoveredMario.setTexture(hoveredMarioTexture);
	hoveredMario.setPosition(bottomRightX, bottomRightY);
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

		isMarioHovered = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].beingHovered())
			{
				isMarioHovered = true;
			}
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
	}

	if (isMarioHovered)
	{
		getWindow()->draw(hoveredMario);
	}
	else
	{
		getWindow()->draw(idleMario);
	}
}


void HomeScene::update(float deltatime) {
	drawMenu();             // Draw buttons
	loopEvents();           // Handle events
}