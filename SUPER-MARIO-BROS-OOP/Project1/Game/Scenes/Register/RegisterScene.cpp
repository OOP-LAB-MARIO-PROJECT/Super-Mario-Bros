#include "RegisterScene.h"
#include <fstream>
#include "../../../Utils/FontManager.h"


RegisterScene::RegisterScene(sf::RenderWindow* window) : Scene(window) {
	float midScreenX = getWindow()->getSize().x / 2.0;
	float midScreenY = getWindow()->getSize().y / 2.0;

	TextBox usernameBox(midScreenX - 200, midScreenY - 100, 400, 50, false);
	TextBox passwordBox(midScreenX - 200, midScreenY, 400, 50, true);
	textBoxes.push_back(usernameBox);
	textBoxes.push_back(passwordBox);

	Button registerGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX - 230, midScreenY + 170), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			addLineIfNotExists();
			showInvalidMessage = true;
		
		}, "Register", 13, sf::Color::Black);
	buttons.push_back(registerGame);

	Button loginGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX + 100, midScreenY + 170), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			SceneManager::getInstance().navigateTo(SceneManager::Scenes::Login);
		}, "Back To Login", 13, sf::Color::Black);
	buttons.push_back(loginGame);

	std::shared_ptr<sf::Font> font = FontManager::getInstance().getFont("Mario");
	if (font == nullptr) {
		std::cerr << "Error: Font 'Mario' not loaded!" << std::endl;
		return;
	}
	inValid.setFont(*font);
	inValid.setString("Mario never forgets a hero! Your account is already registered. Log in to continue saving the day!");
	inValid.setCharacterSize(13);
	inValid.setScale(1, 1.25);
	inValid.setFillColor(sf::Color::Color(251, 188, 174));
	inValid.setPosition(inValid.getScale().x + 3, getWindow()->getSize().y / 2.0 + inValid.getScale().y / 2.0 - 35);
	shape.setSize(sf::Vector2f(getWindow()->getSize().x + 5, inValid.getScale().x + 15));
	shape.setPosition(inValid.getPosition().x - 5, inValid.getPosition().y);
	shape.setFillColor(sf::Color::Color(200, 76, 11));
	shape.setOutlineColor(sf::Color::Black);
}


bool doesLineExist(std::string& newLine) {
	std::ifstream fIN("Game/Scenes/Login/account_manager.txt");
	if (!fIN) {
		std::cout << "Can not open file\n";
	}
	std::string line;
	while (std::getline(fIN, line)) {  
		if (line == newLine) {
			fIN.close();
			return true;  
		}
	}

	fIN.close();
	return false;
}


void RegisterScene::addLineIfNotExists() {
	std::string newLine = textBoxes[0].getText() + " " + textBoxes[1].getText();

	if (doesLineExist(newLine)) {
		isValidMessage = false;
	}
	else {
		
		std::ofstream file("Game/Scenes/Login/account_manager.txt", std::ios::app);
		if (file.is_open()) {
			file << newLine << "\n";  
			file.close();
			isValidMessage = true;
		}
		else {
			std::cerr << "Failed to open the file for writing.\n";
			isValidMessage = false;
		}
	}
}

void RegisterScene::loopEvents() {
	sf::Event event;
	while (getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			getWindow()->close();


		if (event.type == sf::Event::MouseButtonPressed) {
			for (int i = 0; i < textBoxes.size(); i++) {
				bool isSelected = textBoxes[i].isMouseOver(sf::Mouse::getPosition(*(getWindow())));
				textBoxes[i].setSelected(isSelected);
			}
		}

		for (int i = 0; i < textBoxes.size(); i++) {
			if (textBoxes[i].getSelected()) {
				textBoxes[i].handleInput(event);
			}
		}

		for (int i = 0; i < buttons.size(); i++)
		{
			buttons[i].handleEvent(event, *getWindow());
		}
	}
}
void RegisterScene::drawLoginMenu() {
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("UI_Components/UI_Texture_Pack/LoginBackground.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(3.5, 3.3);
	backgroundSprite.setPosition(0, 0);	
	getWindow()->draw(backgroundSprite);

	for (int i = 0; i < textBoxes.size(); i++) {
		textBoxes[i].draw(getWindow());
	}

	for (int i = 0; i < buttons.size(); i++) {
		buttons[i].draw(getWindow());
	}
}

void RegisterScene::drawArgument() {
	if (isValidMessage) {
		std::shared_ptr<sf::Font> font = FontManager::getInstance().getFont("Mario");
		if (font == nullptr) {
			std::cerr << "Error: Font 'Roboto' not loaded!" << std::endl;
			return;
		}

		sf::Text valid;
		valid.setFont(*font);
		valid.setString("The registration is complete. Your epic adventure begins now!");
		valid.setCharacterSize(18);
		valid.setFillColor(sf::Color::Color(251, 188, 174));
		valid.setPosition(0, 450);
		getWindow()->draw(valid);

	}
	else {
		getWindow()->draw(shape);
		getWindow()->draw(inValid);
	}
	
}


void RegisterScene::update(float deltatime) {
	drawLoginMenu();
	if (showInvalidMessage) {
		drawArgument();
	}
	loopEvents();
}