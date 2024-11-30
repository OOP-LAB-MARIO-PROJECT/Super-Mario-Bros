#include "HomeScene.h"

HomeScene::HomeScene(sf::RenderWindow* window) : Scene(window)
{
	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;
	sf::Vector2f midCoordinate(midScreenX - 100, midScreenY - 50); //button base position
	Button startGame = Button::createButton(sf::Vector2f(200, 100), midCoordinate, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); }, "start", 20, sf::Color::Black);
	buttons.push_back(startGame);

	Button exit = Button::createButton(sf::Vector2f(200, 90), sf::Vector2f(midCoordinate.x, midCoordinate.y - 200), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }, "exit", 20, sf::Color::Black); //thay exit bằng hàm thoát game
	buttons.push_back(exit);

	Button setting = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(midCoordinate.x, midCoordinate.y + 210), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Setting); }, "setting", 15, sf::Color::Black); //thay exit bằng hàm thoát game
	buttons.push_back(setting);

	//create mario gif
	std::shared_ptr<sf::Texture> marioTexture  = std::make_shared<sf::Texture>();
	marioTexture->loadFromFile("UI_Components/UI_Texture_Pack/MarioSpriteSheet.png");
	std::shared_ptr <sf::Sprite> marioSprite  = std::make_shared<sf::Sprite>();
	marioSprite->setTexture(*marioTexture); // load texture here so i can calculate the position : D
	sprites.push_back(marioSprite);
	Animation mario = Animation::createAnimation(marioTexture, sf::Vector2u(5, 2), 0.1);
	animations.push_back(mario);
	sprites[0]->setPosition(0, getWindow()->getSize().y - sprites[0]->getTexture()->getSize().y / 4.0); //2 rows so we have to divide by 4 to get the middle of one row
	sprites[0]->setScale(0.5, 0.5);

	//create goomba gif
	std::shared_ptr<sf::Texture> goombaTexture = std::make_shared<sf::Texture>();
	goombaTexture->loadFromFile("UI_Components/UI_Texture_Pack/GoombaSpriteSheet.png");
	std::shared_ptr <sf::Sprite> goombaSprite = std::make_shared<sf::Sprite>();
	goombaSprite->setTexture(*goombaTexture); // load texture here so i can calculate the position : D
	sprites.push_back(goombaSprite);
	Animation goomba = Animation::createAnimation(goombaTexture, sf::Vector2u(5, 1), 0.1);
	animations.push_back(goomba);
	sprites[1]->setPosition(getWindow()->getSize().x / 2.0 - sprites[1]->getTexture()->getSize().x /10.0, getWindow()->getSize().y - sprites[1]->getTexture()->getSize().y / 2.0 - 50); //1 row so we have to divide by 2 to get the middle of one row
	sprites[1]->setScale(1, 1);
	//create pipe 
	/*pipeTexture.loadFromFile("UI_Components/UI_Texture_Pack/pipe.png");
	pipeSprite.setTexture(pipeTexture);
	pipeSprite.setScale(0.5, 0.5);
	pipeSprite.setPosition(getWindow()->getSize().x - pipeTexture.getSize().x, getWindow()->getSize().y - pipeTexture.getSize().y / 2.0);*/
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

	for (int i = 0; i < sprites.size(); ++i)
	{
		getWindow()->draw(*sprites[i]);
	}
//	getWindow()->draw(pipeSprite);
}

void HomeScene::loadGif(float deltatime)
{
	for (int i = 0; i < animations.size(); ++i)
	{
		/*std::cout << animations.size() << std::endl;*/
		animations[i].renderGif(0, deltatime);
		sprites[i]->setTexture(*animations[i].getTexture()); //set texture for sprite, which is a sprite sheet
		sprites[i]->setTextureRect(animations[i].rect); //set the rectangle to display the current image (one of the sprites in the sheet)
	//	sprites[i]->setScale(0.5, 0.5);
	}
	drawMenu();
	loopEvents();
}


void HomeScene::update(float deltatime) {
	loadGif(deltatime);
}