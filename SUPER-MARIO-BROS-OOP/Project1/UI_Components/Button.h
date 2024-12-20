#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include "../Utils/TextureManager.h"
#include "../Utils/FontManager.h"

class Button {
private:
    sf::RectangleShape shape;
    std::shared_ptr<sf::Texture> texture = nullptr;
    std::shared_ptr<sf::Sprite> sprite = nullptr;
    sf::Text text;
    bool isPressed = false;
    bool isHovered = false;
	bool isDisabled = false;
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
    void setFont(const sf::Font& f);
    void setText(const std::string& content, unsigned int textSize, const sf::Color& textColor);
    void setOnClick(const std::function<void()>& callback);
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    void draw(sf::RenderWindow* window);
    static Button createButton(
        const sf::Vector2f& size,
        const sf::Vector2f& position,
        const sf::Color& defaultCol,
        const sf::Color& hoverCol,
        const sf::Color& pressedCol,
        const std::function<void()>& onClickCallback,
        const std::string& content,
        unsigned int textSize,
        const sf::Color& textColor
    );
    bool isButtonPressed();
	bool beingHovered();
};

