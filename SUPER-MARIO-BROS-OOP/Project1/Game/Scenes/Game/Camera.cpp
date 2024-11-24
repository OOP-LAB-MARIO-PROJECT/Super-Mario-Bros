#include "Camera.h"



Camera::Camera(sf::RenderWindow* w) {
	camera = w->getDefaultView();
	//camera.setSize(sf::Vector2f(400, 500));

	leftLimit = 200.0f;
	rightLimit = w->getSize().x - 200.0f;
	aboveLimit = 200.0f;
	beneathLimit = w->getSize().y - 200.0f;
}

void Camera::moveCamera(const float& x, const float& y) {
	leftLimit += x;
	rightLimit += x;
	aboveLimit += y;
	beneathLimit += y;
	camera.setCenter(sf::Vector2f((leftLimit + rightLimit) / 2, (aboveLimit + beneathLimit) / 2));
}

void Camera::setCameraView(sf::RenderWindow* w) {
	w->setView(camera);
}

void Camera::followPlayer(const float& x, const float& y, const float& w, const float& h) {
	if (x <= leftLimit) moveCamera(x - leftLimit, 0);
	else if (x + w >= rightLimit) moveCamera(x + w - rightLimit, 0);

	if (y <= aboveLimit) moveCamera(0, y - aboveLimit);
	else if (y + h >= beneathLimit) moveCamera(0, y + h - beneathLimit);
}


