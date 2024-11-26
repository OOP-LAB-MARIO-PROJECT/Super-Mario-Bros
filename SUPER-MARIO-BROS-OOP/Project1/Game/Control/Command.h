#pragma once

class Command
{
	int cnt = 0;
public:
	virtual void setDeltatime(float deltatime) = 0; // use for overiding
	virtual ~Command() {};
	virtual void execute() = 0;
	virtual void deExecute() = 0;
};