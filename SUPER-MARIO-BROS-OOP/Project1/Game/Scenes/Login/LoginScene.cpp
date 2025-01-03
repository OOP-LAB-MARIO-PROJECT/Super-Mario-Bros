﻿#include "LoginScene.h"
#include <fstream>
#include "../../../Utils/FontManager.h"
#include "../../GameConfig.h"

LoginScene::LoginScene(sf::RenderWindow* window) : Scene(window) {
	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;

	TextBox usernameBox(midScreenX - 200, midScreenY - 100, 400, 50, false);
	TextBox passwordBox(midScreenX - 200, midScreenY, 400, 50, true);
	textBoxes.push_back(usernameBox);
	textBoxes.push_back(passwordBox);


	text.setFont(*(FontManager::getInstance().getFont("Mario")));
	std::string a = "Hehe";
	text.setString(a);
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::White); 
	text.setPosition(200, 400);

	Button loginGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX - 230, midScreenY + 170), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			if (isValidAccount()) {
				std::string username = textBoxes[0].getText();
				GameConfig::getInstance().setPlayerName(username);
				GameConfig::getInstance().loadFromFile();
				SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home);
			}
			else {
				showInvalidMessage = true;
			}
		
		}, "Login", 13, sf::Color::Black);
	buttons.push_back(loginGame);

	Button RegisterGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX + 100, midScreenY + 170), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			SceneManager::getInstance().navigateTo(SceneManager::Scenes::Register);
		}, "Register", 13, sf::Color::Black);
	buttons.push_back(RegisterGame);

	//create title
	titleTexture.loadFromFile("UI_Components/UI_Texture_Pack/Title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setScale(1.5, 1.5);
	titleSprite.setPosition(midScreenX - titleSprite.getScale().x / 2.0 - 255, -2);

	//create hovered flower
	pinkFlower.loadFromFile("UI_Components/UI_Texture_Pack/PinkFlower.png");
	pinkFlowerSprite1.setTexture(pinkFlower);
	pinkFlowerSprite1.setScale(1.5, 1.5);
	pinkFlowerSprite1.setPosition(midScreenX + 125, midScreenY - 170);

	pinkFlowerSprite2.setTexture(pinkFlower);
	pinkFlowerSprite2.setScale(1.5, 1.5);
	pinkFlowerSprite2.setPosition(midScreenX + 125, midScreenY - 70);

	// Tạo đối tượng sf::Text để hiển thị thông báo lỗi
	std::shared_ptr<sf::Font> font = FontManager::getInstance().getFont("Mario");
	if (font == nullptr) {
		std::cerr << "Error: Font 'Roboto' not loaded!" << std::endl;
		return;
	}
	inValid.setFont(*font);
	inValid.setString("Uh-oh! Your username or password missed the mark. Recheck them or register to join the fun!");
	inValid.setCharacterSize(14);
	inValid.setFillColor(sf::Color::Color(251, 188, 174)); // Sử dụng fillColor (đúng với SFML 2.5+)
	inValid.setPosition(inValid.getScale().x + 2, getWindow()->getSize().y / 2.0 + inValid.getScale().y / 2.0 - 35);
	shape.setSize(sf::Vector2f(getWindow()->getSize().x + 3, inValid.getScale().x + 18));
	shape.setPosition(inValid.getPosition().x - 3, inValid.getPosition().y);
	shape.setFillColor(sf::Color::Color(200, 76, 11));
	shape.setOutlineColor(sf::Color::Black);

	//create sad mario
	sadMarioTexture.loadFromFile("UI_Components/UI_Texture_Pack/SadMario.png");
	sadMarioSprite.setTexture(sadMarioTexture);
	sadMarioSprite.setScale(1.5, 1.3);
	sadMarioSprite.setPosition(getWindow()->getSize().x - sadMarioTexture.getSize().x -100, getWindow()->getSize().y - sadMarioTexture.getSize().y - 150);
}


bool LoginScene::isValidAccount() {
	std::string username;
	std::string password;
	std::ifstream fIN("Game/Scenes/Login/account_manager.txt");
	if (!fIN) {
		std::cout << "Can not open file\n";
	}
	bool isValid = false;
	while (fIN >> username >> password) {
		if (username == textBoxes[0].getText() && password == textBoxes[1].getText()) {
			isValid = true;
		}
	}

	fIN.close();

	return isValid;
}

void LoginScene::loopEvents() {
	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		
		

		if (event.type == sf::Event::Closed)
			getWindow()->close();

		if (event.type == sf::Event::MouseButtonPressed) {
			bool selected = false;
			for (int i = 0; i < textBoxes.size(); i++) {
				if (textBoxes[i].isMouseOver(*(getWindow()))) {
					textBoxes[i].setSelected(true);
					selected = true;
					currentBox = i; // Ghi nhận TextBox hiện tại
				}
				else {
					textBoxes[i].setSelected(false);
				}
			}
			beingSelected = selected;
		}

		if (event.type == sf::Event::TextEntered && beingSelected) {
			// Chỉ xử lý TextBox hiện tại
			textBoxes[currentBox].handleInput(event);
		}

		for (int i = 0; i < buttons.size(); i++) {
			buttons[i].handleEvent(event, *getWindow());
		}
	}
}

void LoginScene::drawLoginMenu() {
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/LoginBackground.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(3.5, 3.3);
	backgroundSprite.setPosition(0, 0);
	getWindow()->draw(backgroundSprite);

	getWindow()->draw(titleSprite);

	for (int i = 0; i < textBoxes.size(); i++) {
		textBoxes[i].draw(getWindow());
	}

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].draw(getWindow());
	}

	if (beingSelected && currentBox == 0) 
	{
		getWindow()->draw(pinkFlowerSprite1);
	}
	else if (beingSelected && currentBox == 1) 
	{
		getWindow()->draw(pinkFlowerSprite2);
	}
}

void LoginScene::drawInvalidArgument() {
	getWindow()->draw(shape);
	getWindow()->draw(inValid);
	getWindow()->draw(sadMarioSprite);
}

void LoginScene::update(float deltatime) {
	drawLoginMenu(); //draw the ui elements first and then check for the events
	if (showInvalidMessage) { 
		drawInvalidArgument();
	}
	loopEvents();
}