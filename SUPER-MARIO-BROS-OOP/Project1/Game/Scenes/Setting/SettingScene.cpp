#include "SettingScene.h"

SettingScene::SettingScene(sf::RenderWindow* window) : Scene(window) {
	
	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;
	sf::Vector2f midCoordinate(midScreenX - 100, midScreenY - 50); //button base position
	Button mute = Button::createButton(sf::Vector2f(200, 100), midCoordinate, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[this]() { this->muteHandling();  }, "Mute", 17, sf::Color::Black);
	buttons.push_back(mute);

	Button save = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(midCoordinate.x, midCoordinate.y - 210), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "save\n"; }, "Save", 17, sf::Color::Black);
	buttons.push_back(save);

	Button back = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(midScreenX - 320, midCoordinate.y + 210), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home); }, "Back", 17, sf::Color::Black);
	buttons.push_back(back);

	Button keyBinding = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(midScreenX + 120,  midCoordinate.y + 210), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "keyBinding\n"; }, "Key Binding", 12, sf::Color::Black);
	buttons.push_back(keyBinding);

	volumeSlider = VolumeSlider::createVolumeSlider(sf::Vector2f(200, 20), sf::Vector2f(midScreenX + 210, midScreenY - 25));
}

void SettingScene::changeVolume()
{
	this->volume = volumeSlider.getVolume();
	std::cout << this->volume << '\n';
}

void SettingScene::muteHandling()
{
	if (isClicked == false)
	{
		this->volume = 0;
		isClicked = true;
	}
	else
	{
		this->volume = 50;
		isClicked = false;
	}
}

void SettingScene::saveSetting()
{
	//save setting
}

void SettingScene::changeKeys()
{

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
}

void SettingScene::loopEvents()
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
		volumeSlider.handleEvent(event, *getWindow(), this->isClicked);
		changeVolume();
	}
}

void SettingScene::update(float deltatime)
{
	drawScene();
	loopEvents();
}