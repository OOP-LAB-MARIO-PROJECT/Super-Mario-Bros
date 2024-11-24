#include "SettingScene.h"
SettingScene::SettingScene(sf::RenderWindow* window) : Scene(window) {

	Button mute = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "mute\n";  }, "Mute", 24, sf::Color::Black);
	buttons.push_back(mute);

	Button save = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "save\n"; }, "Save", 24, sf::Color::Black);
	buttons.push_back(save);

	Button back = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(300, 400), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home); }, "Back", 24, sf::Color::Black);
	buttons.push_back(back);

	Button up = Button::createButton(sf::Vector2f(60, 60), sf::Vector2f(520, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "up\n"; }, "Up", 24, sf::Color::Black);
	buttons.push_back(up);

	Button down = Button::createButton(sf::Vector2f(70, 70), sf::Vector2f(600, 250), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "down\n"; }, "Down", 24, sf::Color::Black);
	buttons.push_back(down);

	Button keyBinding = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(550, 400), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { std::cout << "keyBinding\n"; }, "Key Binding", 24, sf::Color::Black);
	buttons.push_back(keyBinding);
}

void SettingScene::changeVolume()
{
	//change volume
}

void SettingScene::saveSetting()
{
	//save setting
}

void SettingScene::changeKeys()
{
	//std::pair<std::string, sf::Keyboard::Key> key;
	//sf::Event event;
	//while (getWindow()->pollEvent(event))
	//{
	//	if (event.type == sf::Event::KeyPressed)
	//	{
	//		key.first = ;
	//		key.second = event.key.code;
	//		keys.insert(key);
	//	}
	//}

}

void SettingScene::drawScene()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(getWindow());
	}
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
	}
}

void SettingScene::update(float deltatime)
{
	drawScene();
	loopEvents();
}