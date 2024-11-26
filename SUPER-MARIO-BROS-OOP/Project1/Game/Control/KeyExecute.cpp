#include "KeyExecute.h"


KeyExecute::~KeyExecute() {
	std::cout << "Called\n";
	for (const std::pair <int, Command*>& pc : mp)
		if (pc.second != nullptr)
			delete pc.second;
};

// add a command with a keyboard code
void KeyExecute::addCommand(int code, Command* command) {
	std::cout << "Added code: " << code << "Command " << command << '\n';
	mp[code] = command;
}

void KeyExecute::handleInput() {
	for (const std::pair <int, Command*>& key : mp)
		if (sf::Keyboard::isKeyPressed((sf::Keyboard::Scancode)key.first)) {
			if (mp.count(key.first) && key.second) key.second->execute();
		}
		else {
			if (mp.count(key.first) && key.second) key.second->deExecute();
		}
}