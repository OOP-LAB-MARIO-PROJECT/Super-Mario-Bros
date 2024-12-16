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
	for (auto it = mp.begin(); it != mp.end(); ++it) {
		if (it->second == command) { //added this new block of code because there
			mp.erase(it); //is a case which there are two distinct keys with the same command
			break;
		}
	}
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
