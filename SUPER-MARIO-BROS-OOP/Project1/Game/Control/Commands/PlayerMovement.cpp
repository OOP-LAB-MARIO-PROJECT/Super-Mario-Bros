#include "PlayerMovement.h"
#include <iostream>

void MoveLeft::setDeltatime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveLeft::execute() {
	player->moveLeft(deltaTime);
}

void MoveLeft::deExecute() {

}

void MoveRight::setDeltatime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveRight::execute() {
	player->moveRight(deltaTime);
}

void MoveRight::deExecute() {
}

void Jump::setDeltatime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void Jump::execute() {
	player->jump(deltaTime);
}

void Jump::deExecute() {
	player->notJump(deltaTime);
}

void MoveUp::setDeltatime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveUp::execute() {
}

void MoveUp::deExecute() {
}

void MoveDown::setDeltatime(float _deltaTime) {
	deltaTime = _deltaTime;
}

void MoveDown::execute() {
}

void MoveDown::deExecute() {
}
