#pragma once
#include <SFML/Graphics.hpp>

class Scene { // no delete window
	sf::RenderWindow* window = nullptr;

public:
	Scene(sf::RenderWindow* window);
	const sf::RenderWindow* getWindow() const;
	void display();
};

