#include "KeyBindingScene.h"
KeyBindingScene::KeyBindingScene(sf::RenderWindow* window) : Scene(window)
{
	gameConfig = &GameConfig::getInstance();
	//for key binding
	/*GameConfig::getInstance().controls.insert({ "Jump", sf::Keyboard::W });
	GameConfig::getInstance().controls.insert({ "Move left", sf::Keyboard::A });
	GameConfig::getInstance().controls.insert({ "Move Right" , sf::Keyboard::D });*/

	Button back = Button::createButton(sf::Vector2f(200, 100), sf::Vector2f(500, 500), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Setting); }, "Back", 17, sf::Color::Black);

	buttons.push_back(back);
	shapes.resize(4);
	sf::RectangleShape shape1;
	shape1.setFillColor(sf::Color::Blue);
	shape1.setSize(sf::Vector2f(200, 100));
	shape1.setPosition(0, 0);
	shapes.push_back(shape1);

	//sf::RectangleShape shape2;
	//shape2.setFillColor(sf::Color::Blue);
	//shape2.setSize(sf::Vector2f(200, 100));
	//shape2.setPosition(0, 100);
	//shapes.push_back(shape2);

	//sf::RectangleShape shape2;
	//shape2.setFillColor(sf::Color::Blue);
	//shape2.setSize(sf::Vector2f(200, 100));
	//shape2.setPosition(0, 100);
	//shapes.push_back(shape2);

	sf::Text action1;
	action1.setFont(*(FontManager::getInstance().getFont("Mario")));
	action1.setString("jump");
	action1.setFillColor(sf::Color::White);
	action1.setCharacterSize(24);
	action1.setPosition(100,50);
	actions.push_back(action1);

	TextBox textBox1(0, 300, 100, 100, false, "W", true);
	//TextBox textBox1(0, 200, 200, 200, false);
	textBoxes.push_back(textBox1);
}

void KeyBindingScene::drawScene()
{
	for (int i = 0; i < shapes.size(); ++i)
	{
		getWindow()->draw(shapes[i]);
	}
	for (int i = 0; i < actions.size(); ++i)
	{
		getWindow()->draw(actions[i]);
		std::cout << "draw action" << i + 1 << '\n';
	}
	for (int i = 0; i < textBoxes.size(); ++i)
	{
		textBoxes[i].draw(getWindow());
	}
	for (int i = 0; i < buttons.size(); ++i)
	{
		buttons[i].draw(getWindow());
	}
}

sf::Keyboard::Key KeyBindingScene::charToKey(char c)
{
	std::unordered_map<char, sf::Keyboard::Key> list = {
		{'a', sf::Keyboard::A},
		{'A', sf::Keyboard::A},
		{'b', sf::Keyboard::B},
		{'B', sf::Keyboard::B},
		{'c', sf::Keyboard::C},
		{'C', sf::Keyboard::C},
		{'d', sf::Keyboard::D},
		{'D', sf::Keyboard::D},
		{'e', sf::Keyboard::E},
		{'E', sf::Keyboard::E},
		{'f', sf::Keyboard::F},
		{'F', sf::Keyboard::F},
		{'g', sf::Keyboard::G},
		{'G', sf::Keyboard::G},
		{'h', sf::Keyboard::H},
		{'H', sf::Keyboard::H},
		{'i', sf::Keyboard::I},
		{'I', sf::Keyboard::I},
		{'j', sf::Keyboard::J},
		{'J', sf::Keyboard::J},
		{'k', sf::Keyboard::K},
		{'K', sf::Keyboard::K},
		{'l', sf::Keyboard::L},
		{'L', sf::Keyboard::L},
		{'m', sf::Keyboard::M},
		{'M', sf::Keyboard::M},
		{'n', sf::Keyboard::N},
		{'N', sf::Keyboard::N},
		{'o', sf::Keyboard::O},
		{'O', sf::Keyboard::O},
		{'p', sf::Keyboard::P},
		{'P', sf::Keyboard::P},
		{'q', sf::Keyboard::Q},
		{'Q', sf::Keyboard::Q},
		{'r', sf::Keyboard::R},
		{'R', sf::Keyboard::R},
		{'s', sf::Keyboard::S},
		{'S', sf::Keyboard::S},
		{'t', sf::Keyboard::T},
		{'T', sf::Keyboard::T},
		{'u', sf::Keyboard::U},
		{'U', sf::Keyboard::U},
		{'v', sf::Keyboard::V},
		{'V', sf::Keyboard::V},
		{'w', sf::Keyboard::W},
		{'W', sf::Keyboard::W},
		{'x', sf::Keyboard::X},
		{'X', sf::Keyboard::X},
		{'y', sf::Keyboard::Y},
		{'Y', sf::Keyboard::Y},
		{'z', sf::Keyboard::Z},
		{'Z', sf::Keyboard::Z}
	};
		if (list.find(c) != list.end()) {
			return list[c];
		}
		else
		{
			return sf::Keyboard::Unknown;
		}
}


void KeyBindingScene::loopEvents()
{
	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			getWindow()->close();
		}

		if (event.type == sf::Event::MouseButtonPressed) 
		{
			for (int i = 0; i < textBoxes.size(); i++) 
			{
				bool isSelected = textBoxes[i].isMouseOver(sf::Mouse::getPosition(*(getWindow())));
				textBoxes[i].setSelected(isSelected);
			}
		}

		beingSelected = false; // for ui design

		for (int i = 0; i < textBoxes.size(); i++) 
		{
			if (textBoxes[i].getSelected())
			{
				beingSelected = true;
				textBoxes[i].handleInput(event);
				std::string enteredText = textBoxes[i].getText();
				char newKey = enteredText[0];
				sf::Keyboard::Key key = charToKey(newKey);
				if (key != sf::Keyboard::Unknown)
				{
					gameConfig->updateControl(actions[i].getString(), key);
				}
			}
			if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
			{
				textBoxes[i].setSelected(false);
				gameConfig->hasKeyChanges = true;
			}
		}
		//debug
		for (auto it = GameConfig::getInstance().controls.begin(); it != GameConfig::getInstance().controls.end(); ++it) {
			std::cout << gameConfig->controls.begin()->first << ' ' << gameConfig->controls.begin()->second << '\n';
		}

		for (int i = 0; i < buttons.size(); ++i)
		{
			buttons[i].handleEvent(event, *getWindow());
		}
	}
}

void KeyBindingScene::update(float deltatime)
{
	drawScene();
	loopEvents();
}