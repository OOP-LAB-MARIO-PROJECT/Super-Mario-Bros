#include "KeyBindingScene.h"

//static void addShape(sf::Vector2f shapePos, sf::Vector2f shapeSize, sf::Color shapeColor, 
//			std::vector<sf::RectangleShape>& shapes) {
//	sf::RectangleShape shape;
//	shape.setFillColor(shapeColor);
//	shape.setSize(shapeSize);
//	shape.setPosition(shapePos);
//	shapes.push_back(shape);
//}

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
	float midScreenX = getWindow()->getSize().x / 2.0 - 70;
	float midScreenY = getWindow()->getSize().y / 2.0 - 35;
	gameConfig = &GameConfig::getInstance();
	//for key binding
	/*GameConfig::getInstance().controls.insert({ "Jump", sf::Keyboard::W });
	GameConfig::getInstance().controls.insert({ "Move left", sf::Keyboard::A });
	GameConfig::getInstance().controls.insert({ "Move Right" , sf::Keyboard::D });*/

	Button back = Button::createButton(sf::Vector2f(200,100), sf::Vector2f(midScreenX - 350, midScreenY + 240), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Setting); }, "Back", 17, sf::Color::Black);

	buttons.push_back(back);

	//back
	backTexture = std::make_shared<sf::Texture>();
	backTexture->loadFromFile("UI_Components/UI_Texture_Pack/back.png");
	backSprite.setTexture(*backTexture);
	backSprite.setScale(0.1, 0.1);

	//create the shapes
	/*shapes.resize(3);
	sf::RectangleShape shape1;
	shape1.setFillColor(sf::Color::Blue);
	shape1.setSize(sf::Vector2f(200, 100));
	shape1.setPosition(0, 0);
	shapes.push_back(shape1);*/

	//sf::RectangleShape shape2;
	//shape2.setFillColor(sf::Color::Blue);
	//shape2.setSize(sf::Vector2f(200, 100));
	//shape2.setPosition(0, 100);
	//shapes.push_back(shape2);

	/*addShape(sf::Vector2f(0, 0), sf::Vector2f(200, 100), sf::Color::Blue, shapes);
	addShape(sf::Vector2f(0, 100), sf::Vector2f(200, 100), sf::Color::Blue, shapes);
	addShape(sf::Vector2f(0, 200), sf::Vector2f(200, 100), sf::Color::Blue, shapes);*/

	//the actual action names
	actualActions.push_back("jump");
	actualActions.push_back("left");
	actualActions.push_back("right");
	actualActions.push_back("dodge");
	actualActions.push_back("shoot");


	TextBox textBox1(midScreenX, midScreenY - 130, 100, 100, false, "W", true);
	TextBox textBox2(midScreenX - 130, midScreenY, 100, 100, false, "A", true);
	TextBox textBox3(midScreenX + 130, midScreenY, 100, 100, false, "D", true);
	TextBox textBox4(midScreenX, midScreenY, 100, 100, false, "S", true);
	TextBox textBox5(midScreenX + 400, midScreenY + 200, 100, 100, false, "F", true);

	//display the arrows
	upArrowTexture.loadFromFile("UI_Components/UI_Texture_Pack/UpArrow.png");
	upArrowSprite.setTexture(upArrowTexture);
	upArrowSprite.setScale(1.0, 1.0);
	upArrowSprite.setPosition(midScreenX + 20, midScreenY - 230);
	sprites.push_back(std::make_shared<sf::Sprite>(upArrowSprite));

	downArrowTexture.loadFromFile("UI_Components/UI_Texture_Pack/DownArrow.png");
	downArrowSprite1.setTexture(downArrowTexture);
	downArrowSprite1.setScale(1.0, 1.0);
	downArrowSprite1.setPosition(midScreenX + 20, midScreenY + 115);
	sprites.push_back(std::make_shared<sf::Sprite>(downArrowSprite1));

	rightArrowTexture.loadFromFile("UI_Components/UI_Texture_Pack/right.png");
	rightArrowSprite.setTexture(rightArrowTexture);
	rightArrowSprite.setScale(1.0, 1.0);
	rightArrowSprite.setPosition(midScreenX + 245, midScreenY + 25);
	sprites.push_back(std::make_shared<sf::Sprite>(rightArrowSprite));


	leftArrowTexture.loadFromFile("UI_Components/UI_Texture_Pack/left.png");
	leftArrowSprite.setTexture(leftArrowTexture);
	leftArrowSprite.setScale(1.0, 1.0);
	leftArrowSprite.setPosition(midScreenX - 210, midScreenY + 25);
	sprites.push_back(std::make_shared<sf::Sprite>(leftArrowSprite));

	leftArrowSprite2.setTexture(leftArrowTexture);
	leftArrowSprite2.setScale(1.0, 1.0);
	leftArrowSprite2.setPosition(midScreenX + 320, midScreenY + 225);
	sprites.push_back(std::make_shared<sf::Sprite>(leftArrowSprite2));

	//display the jelly
	jellyTexture.loadFromFile("UI_Components/UI_Texture_Pack/AngrySun2.png");
	jellySprite.setTexture(jellyTexture);
	jellySprite.setScale(2.5, 2.5);
	jellySprite.setPosition(midScreenX + 230, 40);
	sprites.push_back(std::make_shared<sf::Sprite>(jellySprite));

	//display the foo
	fooTexture.loadFromFile("UI_Components/UI_Texture_Pack/foo.png");
	fooSprite.setTexture(fooTexture);
	fooSprite.setScale(3, 3);
	fooSprite.setPosition(0, 70);
	sprites.push_back(std::make_shared<sf::Sprite>(fooSprite));

	//display the actions
	addActionText("jump", sf::Vector2f(midScreenX + 5, midScreenY - 260), 24, sf::Color::Black, actions);
	addActionText("move left", sf::Vector2f(midScreenX - 425, midScreenY + 40), 24, sf::Color::Black, actions);
	addActionText("move right", sf::Vector2f(midScreenX + 325, midScreenY + 40), 24, sf::Color::Black, actions);
	addActionText("dodge", sf::Vector2f(midScreenX - 5, midScreenY + 195), 24, sf::Color::Black, actions);
	addActionText("shoot", sf::Vector2f(midScreenX + 200, midScreenY + 240), 24, sf::Color::Black, actions);

	textBoxes.push_back(textBox1);
	textBoxes.push_back(textBox2);
	textBoxes.push_back(textBox3);
	textBoxes.push_back(textBox4);
	textBoxes.push_back(textBox5);
}

void KeyBindingScene::drawScene()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/PurpleBackground.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(1.8, 1.2);
	getWindow()->draw(backgroundSprite);

	for (int i = 0; i < sprites.size(); ++i)
	{
		getWindow()->draw(*sprites[i]);
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

	if (beingSelected)
	{
		backSprite.setPosition(buttons[0].getPosition().x + buttons[0].getSize().x - 20, buttons[0].getPosition().y + 5);
		getWindow()->draw(backSprite);
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
			if (buttons[i].beingHovered())
			{
				beingSelected = true;
			}
			buttons[i].handleEvent(event, *getWindow());
		}

	}
}

void KeyBindingScene::update(float deltatime)
{
	drawScene();
	loopEvents();
}