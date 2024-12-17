#include "KeyBindingScene.h"

static void addShape(sf::Vector2f shapePos, sf::Vector2f shapeSize, sf::Color shapeColor, 
			std::vector<sf::RectangleShape>& shapes) {
	sf::RectangleShape shape;
	shape.setFillColor(shapeColor);
	shape.setSize(shapeSize);
	shape.setPosition(shapePos);
	shapes.push_back(shape);
}

static void addActionText(std::string name, sf::Vector2f pos, int charSize, sf::Color color,
		std::vector <sf::Text>& action) {

	sf::Text action1;
	action1.setFont(*(FontManager::getInstance().getFont("Mario")));
	action1.setString(name);
	action1.setFillColor(color);
	action1.setCharacterSize(charSize);
	action1.setPosition(pos);

	action.push_back(action1);

}

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

	//create the shapes

	addShape(sf::Vector2f(0, 0), sf::Vector2f(200, 100), sf::Color::Blue, shapes);
	addShape(sf::Vector2f(0, 100), sf::Vector2f(200, 100), sf::Color::Blue, shapes);
	addShape(sf::Vector2f(0, 200), sf::Vector2f(200, 100), sf::Color::Blue, shapes);

	//display the action

	addActionText("jump", sf::Vector2f(100, 50), 24, sf::Color::White, actions);
	addActionText("move left", sf::Vector2f(100, 150), 24, sf::Color::White, actions);
	addActionText("move right", sf::Vector2f(100, 250), 24, sf::Color::White, actions);
	addActionText("dodge", sf::Vector2f(100, 350), 24, sf::Color::White, actions);
	addActionText("shoot", sf::Vector2f(100, 450), 24, sf::Color::White, actions);

	//the actual action names
	actualActions.push_back("jump");
	actualActions.push_back("left");
	actualActions.push_back("right");
	actualActions.push_back("dodge");
	actualActions.push_back("shoot");

	TextBox textBox1(100, 300, 100, 100, false, "W", true);
	TextBox textBox2(0, 400, 100, 100, false, "A", true);
	TextBox textBox3(200, 400, 100, 100, false, "D", true);
	TextBox textBox4(100, 400, 100, 100, false, "S", true);
	TextBox textBox5(400, 400, 100, 100, false, "F", true);

	textBoxes.push_back(textBox1);
	textBoxes.push_back(textBox2);
	textBoxes.push_back(textBox3);
	textBoxes.push_back(textBox4);
	textBoxes.push_back(textBox5);
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
					//gameConfig->oldKey = gameConfig->controls[actualActions[i]];
					gameConfig->updateControl(actualActions[i], key);
					gameConfig->hasKeyChanges = true;
				}
			}
			/*if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter))
			{
				textBoxes[i].setSelected(false);
				gameConfig->hasKeyChanges = true;
			}*/
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