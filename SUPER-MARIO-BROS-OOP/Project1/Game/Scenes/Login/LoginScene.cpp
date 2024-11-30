#include "LoginScene.h"
#include <fstream>
#include "../../../Utils/FontManager.h"


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

	Button loginGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX - 230, midScreenY + 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			if (isValidAccount()) {
				SceneManager::getInstance().navigateTo(SceneManager::Scenes::Home);
			}
			else {
				showInvalidMessage = true;
			}
		
		}, "Login", 13, sf::Color::Black);
	buttons.push_back(loginGame);

	Button RegisterGame = Button::createButton(sf::Vector2f(150, 70), sf::Vector2f(midScreenX + 100, midScreenY + 100), sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		[&]() {
			SceneManager::getInstance().navigateTo(SceneManager::Scenes::Register);
		}, "Register", 13, sf::Color::Black);
	buttons.push_back(RegisterGame);

	titleTexture.loadFromFile("UI_Components/UI_Texture_Pack/Title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setScale(1.5, 1.5);
	titleSprite.setPosition(midScreenX - titleSprite.getScale().x / 2.0 - 255, -2);
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
}

void LoginScene::drawInvalidArgument() {
	std::shared_ptr<sf::Font> font = FontManager::getInstance().getFont("Roboto");
	if (font == nullptr) {
		std::cerr << "Error: Font 'Roboto' not loaded!" << std::endl;
		return;
	}

	// Tạo đối tượng sf::Text để hiển thị thông báo lỗi
	sf::Text inValid;
	inValid.setFont(*font);
	inValid.setString("Your account is invalid. Please check your username and password again!");
	inValid.setCharacterSize(18);
	inValid.setFillColor(sf::Color::White); // Sử dụng fillColor (đúng với SFML 2.5+)
	inValid.setPosition(200, 450);

	// Vẽ thông báo lên cửa sổ
	getWindow()->draw(inValid);
}


void LoginScene::update(float deltatime) {
	if (showInvalidMessage) {
		drawInvalidArgument();
	}
	drawLoginMenu();
	loopEvents();
}