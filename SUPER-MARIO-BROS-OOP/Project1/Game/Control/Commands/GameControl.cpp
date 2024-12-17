#include "GameControl.h"
#include <iostream>
void Pause::setDeltatime(float _deltatime) {
	coolDown -= _deltatime;
	if (coolDown < 0) coolDown = 0;
}

void Pause::execute() {
	std::cout << "i calling u paursssssssssssss\n";
	if (coolDown > 0) return;
	
	if (!pausing) {
		prev = GameConfig::getInstance().levelStatus;
		GameConfig::getInstance().levelStatus = PAUSE;
	}
	else {
		GameConfig::getInstance().levelStatus = prev;
	}

	pausing = !pausing;
	coolDown = 1.5;
}

void Pause::deExecute() {
}
