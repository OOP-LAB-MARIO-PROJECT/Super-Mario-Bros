#pragma once

class Command
{
	int cnt = 0;
public:
	void setDeltatime(float deltatime) {}; // use for overiding
	virtual ~Command() {};
	virtual void execute() = 0;
	virtual void deExecute() = 0;
};