#include "KeyBindingScene.h"
KeyBindingScene::KeyBindingScene(sf::RenderWindow* window) : Scene(window)
{
	gameConfig = &GameConfig::getInstance();
	int y = 0;
	//for key binding
	/*GameConfig::getInstance().controls.insert({ "Jump", sf::Keyboard::W });
	GameConfig::getInstance().controls.insert({ "Move left", sf::Keyboard::A });
	GameConfig::getInstance().controls.insert({ "Move Right" , sf::Keyboard::D });*/

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
	action1.setString("Jump");
	action1.setFillColor(sf::Color::White);
	action1.setCharacterSize(24);
	action1.setPosition(150,50);

	TextBox textBox1(0, 300, 100, 100, "W");
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
}

void KeyBindingScene::loopEvents()
{
	sf::Event event;
	while (getWindow()->pollEvent(event))
	{
		if (event.type = sf::Event::Closed)
		{
			getWindow()->close();
		}
		beingSelected = false;
		for (int i = 0; i < textBoxes.size(); ++i)
		{
			if (textBoxes[i].getSelected())
			{
				beingSelected = true;
				textBoxes[i].handleInput(event);
			}
		}
	}
}

void KeyBindingScene::update(float deltatime)
{
	drawScene();
	loopEvents();
}