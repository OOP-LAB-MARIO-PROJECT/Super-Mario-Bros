#include "PlayerMovement.h"
#include <iostream>

void MoveLeft::setDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveLeft::execute() {
	player->moveLeft(deltaTime);
}

void MoveLeft::deExecute() {

}

void MoveRight::setDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveRight::execute() {
	player->moveRight(deltaTime);
}

void MoveRight::deExecute() {
}

void Jump::setDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void Jump::execute() {
	player->jump(deltaTime);
}

void Jump::deExecute() {
	player->notJump(deltaTime);
}

void MoveUp::setDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveUp::execute() {
}

void MoveUp::deExecute() {
}

void MoveDown::setDeltaTime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveDown::execute() {
}

void MoveDown::deExecute() {
}
