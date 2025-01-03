﻿#include "SettingScene.h"

SettingScene::SettingScene(sf::RenderWindow* window) : Scene(window) {

	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;
	sf::Vector2f midCoordinate(midScreenX - 95, midScreenY - 45); //button base position

	Button back = Button::createButton(sf::Vector2f(190, 90), sf::Vector2f(midCoordinate.x, midCoordinate.y + 50), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home); }, "Back", 13, sf::Color::Black);
	buttons.push_back(back);

	Button keyBinding = Button::createButton(sf::Vector2f(190, 90), sf::Vector2f(midCoordinate.x, midCoordinate.y - 150), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::KeyBinding); }, "Key Binding", 12, sf::Color::Black);
	buttons.push_back(keyBinding);

	volumeText.setFont(*(FontManager::getInstance().getFont("Mario")));
	volumeText.setFillColor(sf::Color::Color(43, 46, 79));
	volumeText.setCharacterSize(15);
	volumeText.setPosition(sf::Vector2f(310, 26));

	muteIconTexture = std::make_shared<sf::Texture>();
	muteIconTexture->loadFromFile("UI_Components/UI_Texture_Pack/MuteIcon.png");
	muteIconSprite.setTexture(*muteIconTexture);
	muteIconSprite.setScale(0.65, 0.65);
	muteIconSprite.setPosition(0, 0);

	unmuteIconTexture = std::make_shared<sf::Texture>();
	unmuteIconTexture->loadFromFile("UI_Components/UI_Texture_Pack/UnmuteIcon.png");
	unmuteIconSprite.setTexture(*unmuteIconTexture);
	unmuteIconSprite.setScale(0.65, 0.65);
	unmuteIconSprite.setPosition(0, 0);

	volumeSlider = VolumeSlider::createVolumeSlider(sf::Vector2f(200, 18), sf::Vector2f(85, 25));

	//luigi
	luigiTexture = std::make_shared<sf::Texture>();
	luigiTexture->loadFromFile("UI_Components/UI_Texture_Pack/LuigiWithWrench.png");
	luigiSprite.setTexture(*luigiTexture);
	luigiSprite.setScale(0.5, 0.5);
	luigiSprite.setPosition(10, getWindow()->getSize().y - luigiSprite.getLocalBounds().height / 2.0 - 50);

	//wrench
	wrenchTexture = std::make_shared<sf::Texture>();
	wrenchTexture->loadFromFile("UI_Components/UI_Texture_Pack/wrench.png");
	wrenchSprite.setTexture(*wrenchTexture);
	wrenchSprite.setScale(1, 1);

	//back
	backTexture = std::make_shared<sf::Texture>();
	backTexture->loadFromFile("UI_Components/UI_Texture_Pack/back.png");
	backSprite.setTexture(*backTexture);
	backSprite.setScale(0.1, 0.1);

	//talking flower gif
	std::shared_ptr<sf::Texture> talkingFlowerTexture = std::make_shared<sf::Texture>();
	if (talkingFlowerTexture->loadFromFile("UI_Components/UI_Texture_Pack/TalkingFlower.png"))
	{
		std::cout << "texture for talking flower rendered\n" << std::endl;
	}
	std::shared_ptr <sf::Sprite> talkingFlowerSprite = std::make_shared<sf::Sprite>();
	talkingFlowerSprite->setTexture(*talkingFlowerTexture);
	sprites.push_back(talkingFlowerSprite);
	Animation talkingFlower = Animation::createAnimation(talkingFlowerTexture, sf::Vector2u(2, 1), 0.3);
	animations.push_back(talkingFlower);
	sprites[0]->setScale(2, 2);
	sprites[0]->setPosition(800, getWindow()->getSize().y - sprites[0]->getTexture()->getSize().y / 1.0 - talkingFlowerSprite->getGlobalBounds().height - 28);

	//purple flower gif
	std::shared_ptr<sf::Texture> purpleFlowerTexture = std::make_shared<sf::Texture>();
	if (purpleFlowerTexture->loadFromFile("UI_Components/UI_Texture_Pack/purple.png"))
	{
		std::cout << "texture for purple flower rendered\n" << std::endl;
	}
	std::shared_ptr <sf::Sprite> purpleFlowerSprite = std::make_shared<sf::Sprite>();
	purpleFlowerSprite->setTexture(*purpleFlowerTexture);
	sprites.push_back(purpleFlowerSprite);
	Animation purpleFlower = Animation::createAnimation(purpleFlowerTexture, sf::Vector2u(4, 1), 0.3);
	animations.push_back(purpleFlower);
	sprites[1]->setScale(3, 3);
	sprites[1]->setPosition(850, 150);

}

void SettingScene::changeVolume()
{
	this->volume = volumeSlider.getVolume();
	GameConfig::getInstance().setVolume(this->volume);
}

void SettingScene::muteHandling()
{
	if (isMute == false)
	{
		this->volume = 0;
		isMute = true;
	}
	else
	{
		this->volume = 50;
		isMute = false;
	}
}

void SettingScene::drawScene()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/SettingSceneBackground.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.5, 1.8);
	getWindow()->draw(backgroundSprite);
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(getWindow());
	}
	volumeSlider.draw(getWindow());
	getWindow()->draw(volumeText);
	if (isMute)
	{
		getWindow()->draw(muteIconSprite);
	}
	else
	{
		getWindow()->draw(unmuteIconSprite);
	}

	if (isHovered && currentButton == 0)
	{
		backSprite.setPosition(buttons[currentButton].getPosition().x + buttons[currentButton].getSize().x - 20, buttons[currentButton].getPosition().y + 5);
		getWindow()->draw(backSprite);
	}
	else if (isHovered && currentButton == 1)
	{
		wrenchSprite.setPosition(buttons[currentButton].getPosition().x + buttons[currentButton].getSize().x + 10, buttons[currentButton].getPosition().y - 20);
		getWindow()->draw(wrenchSprite);
	}

	getWindow()->draw(luigiSprite);
	for (int i = 0; i < sprites.size(); i++)
	{
		getWindow()->draw(*sprites[i]);
	}
}

void SettingScene::loopEvents()
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(1) << this->volume;
	volumeText.setString(ss.str());
	sf::Event event;
	while (getWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}
		isHovered = false;
		for (int i = 0; i < buttons.size(); i++)
		{
			if (buttons[i].beingHovered())
			{
				isHovered = true;
				currentButton = i;
			}
			buttons[i].handleEvent(event, *getWindow());
		}
		sf::Vector2f mousePos = getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*getWindow()));
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && unmuteIconSprite.getGlobalBounds().contains(mousePos))
		{
			this->muteHandling();
		}
		volumeSlider.handleEvent(event, *getWindow(), this->isMute);
		changeVolume();
	}
}

void SettingScene::loadGif(float deltatime)
{
	for (int i = 0; i < animations.size(); i++)
	{
		animations[i].renderGif(0, deltatime);
		sprites[i]->setTexture(*animations[i].getTexture()); //set texture for sprite, which is a sprite sheet
		sprites[i]->setTextureRect(animations[i].rect); //set the rectangle to display the current image (one of the sprites in the sheet)
	}
	drawScene();
	loopEvents();
}

void SettingScene::update(float deltatime)
{
	loadGif(deltatime);
}