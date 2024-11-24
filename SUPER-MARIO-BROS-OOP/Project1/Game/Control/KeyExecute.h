#pragma once
#include "Command.h"
#
#include "SFML/Graphics.hpp"
#include <map>
#include <iostream>

class KeyExecute
{
	std::map <int, Command*> mp;

public:
	KeyExecute() {};
	~KeyExecute();

	// add a command with a keyboard code
	void addCommand(int code, Command* command);
	void handleInput();
};

