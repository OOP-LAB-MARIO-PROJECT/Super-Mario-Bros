﻿#include "MainMenu.h"

RenderWindow* MainMenu::getWindow()
{
	return window;
}

void MainMenu::setWindow(RenderWindow* window)
{
	this->window = window;
}
void MainMenu::init(RenderWindow* window)
{
	if (!font.loadFromFile("Assets/Fonts/Roboto-Medium.ttf"))
	{
		cout << "Can't load font" << endl;
	}
	options = { "Start", "Exit" };
	textPositions = { Vector2f(300, 250), Vector2f(300, 100) };
	buttonPositions = { Vector2f(400, 250), Vector2f(400, 350) };
	texts.resize(options.size());
	for (int i = 0; i < options.size(); i++)
	{
		texts[i].setFont(font);
		texts[i].setString(options[i]);
		texts[i].setCharacterSize(24);
		texts[i].setFillColor(Color::Black);
		texts[i].setPosition(textPositions[i]);
	}
}

Button MainMenu::getButton(int index)
{
	return buttons[index];
}

MainMenu::MainMenu(RenderWindow* window)
{
	this->window = window;
	cout << "init " << window << '\n';
	Button startGame = Button::createButton(Vector2f(200, 100), Vector2f(300, 250), Color::Yellow, Color::Blue, Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Game); });
	buttons.push_back(startGame);
	Button exit = Button::createButton(Vector2f(200, 100), Vector2f(300, 100), Color::Yellow, Color::Blue, Color::Green,
		[]() { SceneManager::getInstance().navigateTo(SceneManager::Scenes::Exit); }); //thay exit bằng hàm thoát game
	buttons.push_back(exit);
	init(window);
}

MainMenu::~MainMenu()
{
	std::cout << "destrutor called mainmenu\n";
}

void MainMenu::loopEvents()
{
	Event event;
	std::cout << window << '\n';
	while (window->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window->close();
		}
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].handleEvent(event, *window);
			//std::cout << "button " << i << '\n';
		}
		
	}
}

void MainMenu::drawMenu()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i].draw(window);
	}

	for (int i = 0; i < texts.size(); i++)
	{
		window->draw(texts[i]);
	}
}

void MainMenu::runMenu()
{
}
