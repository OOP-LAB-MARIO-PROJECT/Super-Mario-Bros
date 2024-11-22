#pragma once
#include "../Scene.h"
#include "../../../UI/MainMenu.h"

class HomeScene : public Scene
{
	MainMenu* menu = nullptr;
public:
	HomeScene(sf::RenderWindow* window) : Scene(window) {
		menu = new MainMenu(getWindow());
		//menu->init(window);
	};
	~HomeScene() { 
		std::cout << "Destructor homescene\n";
		delete menu; 
	};
	void update(float deltatime) override;
};

