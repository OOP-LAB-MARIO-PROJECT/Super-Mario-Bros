#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/TextureManager.h"
#include <functional>
#include <iostream>

class Button {
private:
    sf::RectangleShape shape;
    bool isPressed = false;
    bool isHovered = false;
    std::function<void()> onClick;

    // Các thuộc tính màu sắc
    sf::Color defaultColor;
    sf::Color hoverColor;
    sf::Color pressedColor;

public:
    // Constructor
    Button(const sf::Vector2f& size, const sf::Vector2f& position);
    // Set and get kích thước
    void setSize(const sf::Vector2f& size);
    sf::Vector2f getSize() const;
    // Set and get vị trí
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    // Set màu sắc cho các trạng thái khác nhau
    void setColors(const sf::Color& defaultCol, const sf::Color& hoverCol, const sf::Color& pressedCol);
    // Set hành động onClick
    void setOnClick(const std::function<void()>& callback);
    // Xử lý sự kiện
    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);
    // Vẽ nút
    void draw(sf::RenderWindow* window);
    // Hàm để tạo nút
    static Button createButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& defaultCol, const sf::Color& hoverCol,
        const sf::Color& pressedCol, const std::function<void()>& onClickCallback);
    bool isButtonPressed();
};


