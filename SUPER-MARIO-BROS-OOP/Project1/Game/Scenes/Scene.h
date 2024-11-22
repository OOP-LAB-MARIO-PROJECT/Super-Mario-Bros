#pragma once
#include <SFML/Graphics.hpp>

/* =======================================
			** USING GUIDE **
------------------------------------------

Interface for using the scene of application:
	- This is sf::RenderWindow* pointer
	- Inherit this class
	- Make sure the constructor should passing the Renderwindow
	- Implement the update(float deltime) method to update the current scene by deltatime

========================================== */

class Scene {
	sf::RenderWindow* window = nullptr; // NO DELETE WINDOW

public:
	Scene();
	Scene(sf::RenderWindow* window);
	sf::RenderWindow* getWindow() const;
	void display();

	virtual void update(float deltatime) = 0;
};

