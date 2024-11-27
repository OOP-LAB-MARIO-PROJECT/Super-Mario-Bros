#include "Camera.h"



Camera::Camera(sf::RenderWindow* w, sf::Vector2f ppos) {
	camera = w->getDefaultView();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int screenWidth = desktop.width / 8;
	int portion = screenWidth * 256 / 16;

	/*
		256 / 16 = screenwidd / x
	*/

	camera.setSize(sf::Vector2f(400, 240));
	leftLimit = ppos.x - 100;
	rightLimit = ppos.x;
	aboveLimit = 200.0f;
	beneathLimit = w->getSize().y - 200.0f;
	base = GameConfig::getInstance().cameraBase;
}

void Camera::moveCamera(const float& x, const float& y) {
	leftLimit += x;
	rightLimit += x;
	aboveLimit += y;
	beneathLimit += y;

	camera.setCenter(sf::Vector2f((leftLimit + rightLimit) / 2, (base + 32 - 104)));
}

void Camera::setCameraView(sf::RenderWindow* w) {
	w->setView(camera);
}

void Camera::followPlayer(const float& x, const float& y, const float& w, const float& h) {
	base = GameConfig::getInstance().cameraBase;
	if (x <= leftLimit) moveCamera(x - leftLimit, 0);
	else if (x + w >= rightLimit) moveCamera(x + w - rightLimit, 0);

	if (y <= aboveLimit) moveCamera(0, y - aboveLimit);
	else if (y + h >= beneathLimit) moveCamera(0, y + h - beneathLimit);
}


