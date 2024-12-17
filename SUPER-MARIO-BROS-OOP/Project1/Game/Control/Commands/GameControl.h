#pragma once
#include "../Command.h"
#include "../../GameConfig.h"
#include <iostream>
//
//class MoveLeft : public Command {
//private:
//
//public:
//	Player* player;
//	float deltaTime;
//	MoveLeft(Player* _player) : player(_player), deltaTime(0) {};
//
//	void setDeltatime(float _deltaTime) override;
//	virtual void execute() override;
//	virtual void deExecute() override;
//
//};

class Pause : public Command {
	bool pausing = false;
	float coolDown = 0;
	LEVEL_STATUS prev = IDLE;
public:
	
	Pause() {
		std::cout << "i have my pause\n";
	}

	void setDeltatime(float _deltatime) override;
	void execute() override;
	void deExecute() override;
};

