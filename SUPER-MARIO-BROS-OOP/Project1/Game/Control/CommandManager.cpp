#include "CommandManager.h"
#include <iostream>
void CommandManager::setDeltaTime(float deltatime) {
	for (const auto& command : myCommand)
		command.second->setDeltatime(deltatime);
}

CommandManager::~CommandManager() {
	for (const auto& command : myCommand)
		delete command.second;
	myCommand.clear();
}

void CommandManager::addCommand(const std::string& name, Command* command) {
	if (myCommand.count(name)) return;
	std::cout << "Command manager added command " << command << ' ' << "with name " << name << '\n';
	myCommand[name] = command;
}

void CommandManager::executeCommand(std::string name) {
	if (!myCommand.count(name)) return;
	myCommand[name]->execute();
}

void CommandManager::deExecuteCommand(std::string name) {
	if (!myCommand.count(name)) return;
	myCommand[name]->deExecute();
}

Command* CommandManager::getCommand(std::string name) {
	if (!myCommand.count(name)) return NULL;
	return myCommand[name];
}
