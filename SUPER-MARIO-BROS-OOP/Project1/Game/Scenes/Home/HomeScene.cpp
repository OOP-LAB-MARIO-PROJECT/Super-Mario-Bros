#include "HomeScene.h"

void HomeScene::update(float deltatime)
{
	menu->drawMenu();
	menu->loopEvents();
}
