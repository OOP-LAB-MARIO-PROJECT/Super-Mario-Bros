#include "CommandManager.h"



void CommandManager::setDeltaTime(float deltatime) {

}

void CommandManager::addCommand(const std::string& name, std::unique_ptr<Command> command) {

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
	return myCommand[name].get();
}
