#pragma once
#include "Command.h"
#include <map>
#include <string>
#include <memory>

class CommandManager {
	std::map <std::string, Command*> myCommand;

public:

	CommandManager() {};
	~CommandManager();
	void setDeltaTime(float deltatime);

	void addCommand(const std::string& name, Command* command);

	void executeCommand(std::string name);
	void deExecuteCommand(std::string name);
	
	Command* getCommand(std::string name);
};

