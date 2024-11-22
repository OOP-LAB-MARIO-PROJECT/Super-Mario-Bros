#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>

class Button {
private:
    sf::RectangleShape shape;
    bool isPressed = false;
    bool isHovered = false;
    std::function<void()> onClick;

    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color pressedColor;

public:
    // Constructor
    Button(const sf::Vector2f& size, const sf::Vector2f& position);
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    void setColors(const sf::Color& defaultCol, const sf::Color& hoverCol, const sf::Color& pressedCol);
    void setOnClick(const std::function<void()>& callback);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow* window);
    static Button createButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& defaultCol, const sf::Color& hoverCol,
        const sf::Color& pressedCol, const std::function<void()>& onClickCallback);
    bool isButtonPressed();
};

