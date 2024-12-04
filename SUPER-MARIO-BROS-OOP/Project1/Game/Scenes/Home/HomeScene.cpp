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
	std::shared_ptr <sf::Sprite> goombaSprite1 = std::make_shared<sf::Sprite>();
	goombaSprite1->setTexture(*goombaTexture); // load texture here so i can calculate the position : D
	sprites.push_back(goombaSprite1);
	Animation goomba1 = Animation::createAnimation(goombaTexture, sf::Vector2u(5, 1), 0.1);
	animations.push_back(goomba1);
	sprites[1]->setPosition(getWindow()->getSize().x - goomba1.getTexture()->getSize().x + 300, getWindow()->getSize().y - sprites[0]->getTexture()->getSize().y / 4.0); //1 row so we have to divide by 2 to get the middle of one row
	sprites[1]->setScale(2, 2);

	//create coin gifs
	std::shared_ptr<sf::Texture> coinTexture = std::make_shared<sf::Texture>();
	coinTexture->loadFromFile("UI_Components/UI_Texture_Pack/CoinSpriteSheet.png");
	std::shared_ptr <sf::Sprite> coinSprite1 = std::make_shared<sf::Sprite>();
	std::shared_ptr <sf::Sprite> coinSprite2 = std::make_shared<sf::Sprite>();
	std::shared_ptr <sf::Sprite> coinSprite3 = std::make_shared<sf::Sprite>();
	std::shared_ptr <sf::Sprite> coinSprite4 = std::make_shared<sf::Sprite>();	
	std::shared_ptr <sf::Sprite> coinSprite5 = std::make_shared<sf::Sprite>();
	coinSprite1->setTexture(*coinTexture); // load texture here so i can calculate the position : D
	coinSprite2->setTexture(*coinTexture);
	coinSprite3->setTexture(*coinTexture);
	coinSprite4->setTexture(*coinTexture);
	coinSprite5->setTexture(*coinTexture);

	sprites.push_back(coinSprite1);
	sprites.push_back(coinSprite2);
	sprites.push_back(coinSprite3);
	sprites.push_back(coinSprite4);
	sprites.push_back(coinSprite5);

	Animation coin1 = Animation::createAnimation(coinTexture, sf::Vector2u(5, 1), 0.1);
	Animation coin2 = Animation::createAnimation(coinTexture, sf::Vector2u(5, 1), 0.1);
	Animation coin3 = Animation::createAnimation(coinTexture, sf::Vector2u(5, 1), 0.1);
	Animation coin4 = Animation::createAnimation(coinTexture, sf::Vector2u(5, 1), 0.1);
	Animation coin5 = Animation::createAnimation(coinTexture, sf::Vector2u(5, 1), 0.1);

	animations.push_back(coin1);
	animations.push_back(coin2);
	animations.push_back(coin3);
	animations.push_back(coin4);
	animations.push_back(coin5);

	sprites[2]->setPosition(startGame.getPosition().x + 100, startGame.getPosition().y + 100);
	sprites[3]->setPosition(startGame.getPosition().x - sprites[3]->getTexture()->getSize().x / 8.0, startGame.getPosition().y - sprites[3]->getTexture()->getSize().y / 2.0);
	sprites[4]->setPosition(exit.getPosition().x + exit.getSize().x, exit.getPosition().y - exit.getSize().y);
	sprites[5]->setPosition(setting.getPosition().x - setting.getSize().x + 40, setting.getPosition().y);
	sprites[6]->setPosition(exit.getPosition().x - exit.getSize().x + 50, exit.getPosition().y - exit.getSize().y);

	sprites[2]->setScale(1, 1);
	sprites[3]->setScale(1, 1);
	sprites[4]->setScale(1, 1);
	sprites[5]->setScale(1, 1);
	sprites[6]->setScale(1, 1);

	// create moons
	startTexture.loadFromFile("UI_Components/UI_Texture_Pack/YellowMoon.png");
	startSprite.setTexture(startTexture);

	
	exitTexture.loadFromFile("UI_Components/UI_Texture_Pack/Moon.png");
	exitSprite.setTexture(exitTexture);
	

	settingTexture.loadFromFile("UI_Components/UI_Texture_Pack/OrangeMoon.png");
	settingSprite.setTexture(settingTexture);
	settingSprite.setScale(0.75, 0.75);

	//create koopa
	std::shared_ptr <sf::Sprite> goombaSprite2 = std::make_shared<sf::Sprite>();
	goombaSprite2->setTexture(*goombaTexture); // load texture here so i can calculate the position : D
	sprites.push_back(goombaSprite2);
	Animation goomba2 = Animation::createAnimation(goombaTexture, sf::Vector2u(5, 1), 0.1);
	animations.push_back(goomba1);
	sprites[7]->setPosition(getWindow()->getSize().x - goomba2.getTexture()->getSize().x + 450, getWindow()->getSize().y - sprites[0]->getTexture()->getSize().y / 4.0); //1 row so we have to divide by 2 to get the middle of one row
	sprites[7]->setScale(2, 2);

	//create left pipes
	pipeTexture.loadFromFile("UI_Components/UI_Texture_Pack/pipe.png");
	leftPipeSprite1.setTexture(pipeTexture);
	leftPipeSprite2.setTexture(pipeTexture);
	leftPipeSprite3.setTexture(pipeTexture);

	leftPipeSprite1.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);
	leftPipeSprite2.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);
	leftPipeSprite3.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);

	leftPipeSprite1.setRotation(90);
	leftPipeSprite2.setRotation(90);
	leftPipeSprite3.setRotation(90);

	leftPipeSprite1.setScale(2, 2);
	leftPipeSprite2.setScale(2, 2);
	leftPipeSprite3.setScale(2, 2);

	leftPipeSprite1.setPosition(leftPipeSprite1.getScale().x + leftPipeSprite1.getOrigin().x, leftPipeSprite1.getOrigin().y);
	leftPipeSprite2.setPosition(leftPipeSprite1.getScale().x + leftPipeSprite1.getOrigin().x, leftPipeSprite1.getPosition().y + 200);
	leftPipeSprite3.setPosition(leftPipeSprite1.getScale().x + leftPipeSprite1.getOrigin().x, leftPipeSprite1.getPosition().y + 400);

	sprites.push_back(std::make_shared<sf::Sprite>(leftPipeSprite1));
	sprites.push_back(std::make_shared<sf::Sprite>(leftPipeSprite2));
	sprites.push_back(std::make_shared<sf::Sprite>(leftPipeSprite3));

	//create right pipes
	rightPipeSprite1.setTexture(pipeTexture);
	rightPipeSprite2.setTexture(pipeTexture);
	rightPipeSprite3.setTexture(pipeTexture);

	rightPipeSprite1.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);
	rightPipeSprite2.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);
	rightPipeSprite3.setOrigin(pipeTexture.getSize().x / 2.0, pipeTexture.getSize().y / 2.0);

	rightPipeSprite1.setRotation(270);
	rightPipeSprite2.setRotation(270);
	rightPipeSprite3.setRotation(270);

	rightPipeSprite1.setScale(2, 2);
	rightPipeSprite2.setScale(2, 2);
	rightPipeSprite3.setScale(2, 2);

	rightPipeSprite1.setPosition(getWindow()->getSize().x - rightPipeSprite1.getScale().x - rightPipeSprite1.getOrigin().x, rightPipeSprite1.getOrigin().y);
	rightPipeSprite2.setPosition(getWindow()->getSize().x - rightPipeSprite1.getScale().x - rightPipeSprite1.getOrigin().x, rightPipeSprite1.getPosition().y + 200);
	rightPipeSprite3.setPosition(getWindow()->getSize().x - rightPipeSprite1.getScale().x - rightPipeSprite1.getOrigin().x, rightPipeSprite1.getPosition().y + 400);

	sprites.push_back(std::make_shared<sf::Sprite>(rightPipeSprite1));
	sprites.push_back(std::make_shared<sf::Sprite>(rightPipeSprite2));
	sprites.push_back(std::make_shared<sf::Sprite>(rightPipeSprite3));

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
		isMoonHovered = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].beingHovered())
			{
				isMoonHovered = true;
				currentMoon = i;
			}
			buttons[i].handleEvent(event, *getWindow());
		}
	}
}


void HomeScene::drawMenu()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/Background.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.75, 1.78);
	getWindow()->draw(backgroundSprite);
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(getWindow());
	}

	if (isMoonHovered && currentMoon == 0)
	{
		startSprite.setPosition(buttons[currentMoon].getPosition().x + buttons[currentMoon].getSize().x + 60, buttons[currentMoon].getPosition().y - 50);
		getWindow()->draw(startSprite);
	}
	else if (isMoonHovered && currentMoon == 1)
	{
		exitSprite.setPosition(buttons[currentMoon].getPosition().x + buttons[currentMoon].getSize().x + 60, buttons[currentMoon].getPosition().y - 50);
		getWindow()->draw(exitSprite);
	}
	else if (isMoonHovered && currentMoon == 2)
	{
		settingSprite.setPosition(buttons[currentMoon].getPosition().x + buttons[currentMoon].getSize().x + 60, buttons[currentMoon].getPosition().y - 50);
		getWindow()->draw(settingSprite);
	}

	for (int i = 0; i < sprites.size(); ++i)
	{
		getWindow()->draw(*sprites[i]);
	}
}

void HomeScene::loadGif(float deltatime)
{
	for (int i = 0; i < animations.size(); ++i)
	{
		/*std::cout << animations.size() << std::endl;*/
		animations[i].renderGif(0, deltatime);
		sprites[i]->setTexture(*animations[i].getTexture()); //set texture for sprite, which is a sprite sheet
		sprites[i]->setTextureRect(animations[i].rect); //set the rectangle to display the current image (one of the sprites in the sheet)
	}
	drawMenu();
	loopEvents();
}


void HomeScene::update(float deltatime) {
	loadGif(deltatime);
}