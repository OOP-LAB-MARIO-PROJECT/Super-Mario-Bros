#pragma once
#include "Command.h"
#include <map>
#include <string>
#include <memory>

class CommandManager {
	std::map <std::string, std::unique_ptr <Command>> myCommand;

public:

	CommandManager() {};
	void setDeltaTime(float deltatime);

	void addCommand(const std::string& name, std::unique_ptr<Command> command);

	void executeCommand(std::string name);
	void deExecuteCommand(std::string name);
	
	Command* getCommand(std::string name);
};

