#include "Button.h"


Button::Button(const sf::Vector2f& size, const sf::Vector2f& position)
    : shape(size), defaultColor(sf::Color::Transparent), hoverColor(sf::Color::Transparent), pressedColor(sf::Color::Transparent) {
	shape.setPosition(position);
    shape.setSize(size);
    shape.setFillColor(defaultColor); 
    sprite = NULL;
}

void Button::setSize(const sf::Vector2f& size) {
    shape.setSize(size);
}

sf::Vector2f Button::getSize() const {
    return shape.getSize();
}


void Button::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
}

sf::Vector2f Button::getPosition() const {
    return shape.getPosition();
}


void Button::setColors(const sf::Color& defaultCol, const sf::Color& hoverCol, const sf::Color& pressedCol) {
    defaultColor = defaultCol;
    hoverColor = hoverCol;
    pressedColor = pressedCol;
    shape.setFillColor(defaultColor); 
}

void Button::setFont(const sf::Font& f) {
    text.setFont(f); 
}


void Button::setText(const std::string& content, unsigned int textSize, const sf::Color& textColor) {
    if (content.empty()) {
        std::cerr << "Text content is empty!" << std::endl;
    }
    text.setString(content);
    text.setCharacterSize(textSize);
    text.setFillColor(textColor);

	this->textColor = textColor;

    sf::FloatRect bounds = shape.getGlobalBounds();
    sf::FloatRect textBounds = text.getGlobalBounds();
    text.setPosition((bounds.left + (bounds.width - textBounds.width) / 2.0f), bounds.top + (bounds.height - textBounds.height) / 2.0f - 5.0f);
}


void Button::setOnClick(const std::function<void()>& callback) {
    onClick = callback;
}

bool Button::beingHovered()
{
	return isHovered;
}

void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window){
    
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    isHovered = shape.getGlobalBounds().contains(mousePos);
    if (isHovered) {
        shape.setFillColor(hoverColor); 
        text.setFillColor(sf::Color::Color(107, 137, 253));
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			text.setCharacterSize(text.getCharacterSize() + 5);
            isPressed = true;
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            text.setCharacterSize(text.getCharacterSize() - 5);
            if (isPressed && onClick) {
                onClick(); 
            }
            isPressed = false;
        }
    }
    else {
        shape.setFillColor(defaultColor); 
        text.setFillColor(getTextColor());
   }
}


void Button::draw(sf::RenderWindow* window) {
    if (sprite) window->draw(*sprite);
   /* std::cout << "draw sprite\n";*/
    window->draw(shape);
   /* std::cout << "draw shape\n";*/
    window->draw(text);
    /*std::cout << "draw text\n";*/
}

Button Button::createButton(
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& defaultCol,
    const sf::Color& hoverCol,
    const sf::Color& pressedCol,
    const std::function<void()>& onClickCallback,
    const std::string& content, 
    unsigned int textSize, 
    const sf::Color& textColor
    ) {
    Button button(size, position);

    button.texture = std::make_shared<sf::Texture>();
    if (button.texture->loadFromFile("UI_Components/UI_Texture_Pack/cloud.png"))
    {
        std::cout << "texture rendered" << std::endl;
    }
    button.sprite = std::make_shared<sf::Sprite>();
    button.sprite->setTexture(*(button.texture));
    float midX = size.x / 2.0;
    float midY = size.y / 2.0;
    sf::Vector2u textureSize = button.texture->getSize();
    float spriteX = (size.x / textureSize.x) * 2;
	float spriteY = (size.y / textureSize.y) * 2;
    button.sprite->setScale(spriteX, spriteY);
    button.sprite->setPosition(position.x - midX, position.y - midY  - 50.0);
    button.setFont(*(FontManager::getInstance().getFont("Mario")));
    button.setText(content, textSize, textColor);
    button.setOnClick(onClickCallback); 
    return button;
}

Button Button::createButton(
    const sf::Vector2f& size,
    const sf::Vector2f& position,
    const sf::Color& defaultCol,
    const sf::Color& hoverCol,
    const sf::Color& pressedCol,
    const std::function<void()>& onClickCallback,
    const std::string& content,
    unsigned int textSize,
    const sf::Color& textColor,
	std::string texturePath
) {
    Button button(size, position);

    button.texture = std::make_shared<sf::Texture>();
    if (!button.texture->loadFromFile(texturePath))
    {
        std::cout << "ver2" << std::endl;
    }
    button.sprite = std::make_shared<sf::Sprite>();
    button.sprite->setTexture(*(button.texture));
    float midX = size.x / 2.0;
    float midY = size.y / 2.0;
    sf::Vector2u textureSize = button.texture->getSize();
    button.sprite->setScale(1.3, 1.3);
    button.sprite->setPosition(position.x, position.y + midY);
    button.setFont(*(FontManager::getInstance().getFont("Mario")));
    button.setText(content, textSize, textColor);
    button.text.setOutlineColor(sf::Color::Black);
    button.text.setOutlineThickness(2);
    button.setOnClick(onClickCallback);
    return button;
}


bool Button::isButtonPressed()
{
    return isPressed;
}

sf::Color Button::getTextColor()
{
	return textColor;
}