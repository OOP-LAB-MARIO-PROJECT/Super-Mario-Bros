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

TextBox::TextBox(float x, float y, float width, float height, bool isPassword, std::string defaultText, bool hasLim)
    : isPassword(isPassword), textEntered(defaultText), isSelected(false), hasLimit(hasLim) {

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

void TextBox::handleInput(sf::Event event) {
    if (isSelected && event.type == sf::Event::TextEntered) {

        if (hasLimit && textEntered.length() == 1) {
            if (!std::isalpha(event.text.unicode)) return;
            textEntered.pop_back();
        }

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

bool TextBox::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePixelPos);

    return box.getGlobalBounds().contains(mouseWorldPos);
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

