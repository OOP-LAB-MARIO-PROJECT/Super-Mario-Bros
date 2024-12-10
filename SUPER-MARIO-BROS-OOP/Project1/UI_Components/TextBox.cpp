#include "Textbox.h"

TextBox::TextBox(float x, float y, float width, float height, bool isPassword)
    : isPassword(isPassword), textEntered(""), isSelected(false) {

    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(10);

    text.setFont(*(FontManager::getInstance().getFont("Mario")));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);


    text.setPosition(x + 10, y + 10);
}

TextBox::TextBox(float x, float y, float width, float height, std::string defaulText)
{
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(10);

    text.setString(defaulText);
    text.setFont(*(FontManager::getInstance().getFont("Mario")));
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(24);
    text.setPosition(x + 10, y + 10);
}

void TextBox::handleInput(sf::Event event) {
    if (isSelected && event.type == sf::Event::TextEntered) {
        
        if (event.text.unicode == 8 && textEntered.length() > 0) { 
            textEntered.pop_back();
        }
        else if (event.text.unicode < 128 && event.text.unicode != 8) {  
            textEntered += static_cast<char>(event.text.unicode);
        }
    }
}

void TextBox::draw(sf::RenderWindow* window) {
    window->draw(box);

    std::string displayText = isPassword ? std::string(textEntered.length(), '*') : textEntered;
    text.setString(displayText);

    window->draw(text);
}

std::string TextBox::getText() const {
    return textEntered;
}

bool TextBox::isMouseOver(sf::Vector2i mousePos) {
    return box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}

void TextBox::setSelected(bool selected) {
    isSelected = selected;
    if (isSelected) {
        box.setOutlineColor(sf::Color::Blue);
    }
    else {
        box.setOutlineColor(sf::Color::Black);
    }
}

bool TextBox::getSelected() {
    return isSelected;
}