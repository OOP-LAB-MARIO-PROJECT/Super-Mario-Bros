#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window)
{
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

	marioTexture = std::make_shared<sf::Texture>();
	if (marioTexture->loadFromFile("UI_Components/UI_Texture_Pack/MarioSpriteSheet.png"))
	{
		std::cout << "Load mario texture successfully" << std::endl;
	}
	else
	{
		std::cout << "Load mario texture failed" << std::endl;
	}
	marioSprite = std::make_shared<sf::Sprite>();
	marioSprite->setTexture(*marioTexture);
	marioAnimation = Animation(marioTexture, sf::Vector2u(5, 2), 0.1);

	pipeTexture = std::make_shared<sf::Texture>();
	pipeSprite = std::make_shared<sf::Sprite>();
	if (pipeTexture->loadFromFile("UI_Components/UI_Texture_Pack/pipe.png"))
	{
		std::cout << "Load pipe texture successfully" << std::endl;
	}
	else
	{
		std::cout << "Load pipe texture failed" << std::endl;
	}
	pipeSprite->setTexture(*pipeTexture);
	//pipeSprite->setPosition();
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
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(getWindow());
	}
	getWindow()->draw(*marioSprite);
}

void HomeScene::render(float deltatime)
{
	marioAnimation.renderGif(0, deltatime);

	marioSprite->setTextureRect(marioAnimation.rect);
	sf::Vector2f bottomLeft(0, getWindow()->getSize().y - marioAnimation.rect.height);
	marioSprite->setPosition(bottomLeft);
	marioSprite->setScale(0.5, 0.5);
	drawMenu();
	loopEvents();
}


void HomeScene::update(float deltatime) {
	render(deltatime);
}