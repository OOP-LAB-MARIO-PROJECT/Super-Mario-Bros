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
	if (x <= leftLimit) moveCamera(x - leftLimit, 0);
	else if (x + w >= rightLimit) moveCamera(x + w - rightLimit, 0);

	if (y <= aboveLimit) moveCamera(0, y - aboveLimit);
	else if (y + h >= beneathLimit) moveCamera(0, y + h - beneathLimit);
}

void Camera::renderGameInfo(sf::RenderWindow* window, sf::Font& font, const GameConfig& config) {

	sf::Text playerNameText("Player: " + config.playerName, font, 20);

	playerNameText.setPosition(camera.getCenter().x, camera.getCenter().y);

	sf::Text levelText("Level: " + config.currentLevel, font, 20);
	levelText.setPosition(playerNameText.getPosition().x, playerNameText.getPosition().y + 30);

	sf::Text scoreText("Score: " + std::to_string(config.score), font, 20);
	scoreText.setPosition(levelText.getPosition().x, levelText.getPosition().y + 30);

	sf::Text coinText("Coins: " + std::to_string(config.coins), font, 20);
	coinText.setPosition(scoreText.getPosition().x, scoreText.getPosition().y + 30);

	sf::Text timeText("Time: " + std::to_string(config.timeLeft) + "s", font, 20);
	timeText.setPosition(coinText.getPosition().x, coinText.getPosition().y + 30);

	sf::Text volumeText("Volume: " + std::to_string(static_cast<int>(config.volume)) + "%", font, 20);
	volumeText.setPosition(timeText.getPosition().x, timeText.getPosition().y + 30);

	window->draw(playerNameText);
	window->draw(levelText);
	window->draw(scoreText);
	window->draw(coinText);
	window->draw(timeText);
	window->draw(volumeText);
}