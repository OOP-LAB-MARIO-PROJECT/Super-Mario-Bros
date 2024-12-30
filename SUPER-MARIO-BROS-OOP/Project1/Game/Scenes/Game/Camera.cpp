#include "Camera.h"

Camera::Camera(sf::RenderWindow* w, sf::Vector2f ppos) : backhome(sf::Vector2f(0, 0), sf::Vector2f(100, 50)) {
	camera = w->getDefaultView();
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int screenWidth = desktop.width / 8;
	int portion = screenWidth * 256 / 16;

	/*
		256 / 16 = screenwidd / x
	*/

	camera.setSize(sf::Vector2f(width, height));
	leftLimit = ppos.x - 100;
	rightLimit = ppos.x;
	aboveLimit = 200.0f;
	beneathLimit = w->getSize().y - 200.0f;
	base = GameConfig::getInstance().cameraBase;

	backhome.setSize(sf::Vector2f(40, 20));
	backhome.setOnClick(
		[]() {
			SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home);
		}
	);
	/*
	
    button.setFont(*(FontManager::getInstance().getFont("Mario")));
    button.setText(content, textSize, textColor);
	*/
	backhome.setFont(*(FontManager::getInstance().getFont("Roboto")));
	backhome.setText("Home", 10, sf::Color::White);
	backhome.setColors(sf::Color(117, 78, 26), sf::Color::Yellow, sf::Color::Green);
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
	camera.setCenter(sf::Vector2f((leftLimit + rightLimit) / 2, (base + 32 - 104)));
}

void Camera::renderGameInfo(sf::RenderWindow* window, sf::Font& font, const GameConfig& config, CommandManager& command) {

	int fontSize = 100;
	sf::Vector2f scale(0.1, 0.1);

	sf::Text playerNameText("Player: " + config.playerName, font, fontSize);
 	sf::Text levelText("Level: " + config.currentLevel, font, fontSize);
	sf::Text scoreText("Score: " + std::to_string(config.score), font, fontSize);
	sf::Text coinText("Coins: " + std::to_string(config.coins), font, fontSize);
	sf::Text timeText("Time: " + std::to_string((int)config.timeLeft) + "s", font, fontSize);
	sf::Text volumeText("Volume: " + std::to_string(static_cast<int>(config.volume)) + "%", font, fontSize);

	if (--pauseTimer <= 0) {
		pauseTimer = 10;
		pausText += '.';
		if (pausText.size() > 15) pausText = "Pausing";
	}

	sf::Text pausingText(pausText , font, fontSize);

	playerNameText.setScale(scale);
	levelText.setScale(scale);
	scoreText.setScale(scale);
	coinText.setScale(scale);
	timeText.setScale(scale);
	volumeText.setScale(scale);
	pausingText.setScale(scale);

	float textYpos = camera.getCenter().y - 116.f;
	playerNameText.getGlobalBounds().getPosition();

	sf::Vector2f sizeP = pausingText.getGlobalBounds().getSize();
	pausingText.setPosition(camera.getCenter() - sizeP / 2.f);
	sizeP.x = -20;

	backhome.setPosition(camera.getCenter() + sizeP);

	auto spaceFrom = [&](const sf::Text& rect, float space) {
		sf::Vector2f res = rect.getPosition();
		res.x += rect.getGlobalBounds().getSize().x + space;
		res.y = rect.getPosition().y;
		return res;
	};
	
	playerNameText.setPosition(camera.getCenter().x - 190, textYpos);
	levelText.setPosition(spaceFrom(playerNameText, 10));
	scoreText.setPosition(spaceFrom(levelText, 10));
	coinText.setPosition(spaceFrom(scoreText, 10));
	timeText.setPosition(spaceFrom(coinText, 10));
	volumeText.setPosition(spaceFrom(timeText, 10));

	window->draw(playerNameText);
	window->draw(levelText);
	window->draw(scoreText);
	window->draw(coinText);
	window->draw(timeText);
	window->draw(volumeText);

	if (GameConfig::getInstance().levelStatus == PAUSE) {
		window->draw(pausingText);
		backhome.draw(window);
		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}


			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Escape) {
					command.executeCommand("pause");
				}

			backhome.handleEvent(event, *window);
		}
	}
}

std::pair <sf::Vector2f, sf::Vector2f> Camera::getRenderSpace() {
	sf::Vector2f center = camera.getCenter();
	sf::Vector2f size = sf::Vector2f(width, height);
	center.x -= width / 2.f;
	center.y -= height / 2.f;

	return { center, size };
}
