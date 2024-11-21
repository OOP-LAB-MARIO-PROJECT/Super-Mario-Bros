#include "HomeScene.h"

void HomeScene::update(float deltatime)
{
	RenderWindow* window = const_cast<RenderWindow*>(getWindow());
	MainMenu mainMenu(window);
	mainMenu.drawMenu();
	mainMenu.loopEvents();
}
