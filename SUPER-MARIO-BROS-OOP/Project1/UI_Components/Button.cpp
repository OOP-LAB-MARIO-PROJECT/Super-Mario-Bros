#include "Button.h"


Button::Button(const sf::Vector2f& size, const sf::Vector2f& position)
    : shape(size), defaultColor(sf::Color::Blue), hoverColor(sf::Color::Green), pressedColor(sf::Color::Red) {
    shape.setPosition(position);
    shape.setFillColor(defaultColor); // Màu mặc định
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

// Set màu sắc cho các trạng thái khác nhau
void Button::setColors(const sf::Color& defaultCol, const sf::Color& hoverCol, const sf::Color& pressedCol) {
    defaultColor = defaultCol;
    hoverColor = hoverCol;
    pressedColor = pressedCol;
    shape.setFillColor(defaultColor); // Cập nhật màu sắc hiện tại
}

// Set hành động onClick
void Button::setOnClick(const std::function<void()>& callback) {
    onClick = callback;
}

// Xử lý sự kiện
void Button::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    // Kiểm tra chuột có đang hover nút không
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    isHovered = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    //std::cout << mousePos.x << ' ' << mousePos.y << ' ' << shape.getPosition().x << ' ' << isHovered << '\n';
    if (isHovered) {
        shape.setFillColor(hoverColor); // Màu khi hover
        std::cout << "changed color\n";
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            isPressed = true;
            shape.setFillColor(sf::Color::Magenta); // Màu khi nhấn
            std::cout << "press color " << (pressedColor == sf::Color::Yellow) << '\n';
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (isPressed && onClick) {
                std::cout << "I will execute a command\n";
                onClick(); // Gọi hàm khi nhấn
            }
            isPressed = false;
        }
    }
    else {
        shape.setFillColor(defaultColor); // Màu mặc định khi không hover
    }
}

// Vẽ nút
void Button::draw(sf::RenderWindow* window) {
    window->draw(shape);
}

Button Button::createButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& defaultCol, const sf::Color& hoverCol,
    const sf::Color& pressedCol, const std::function<void()>& onClickCallback) {
    Button button(size, position); 
    button.setColors(defaultCol, hoverCol, pressedCol); 
    button.setOnClick(onClickCallback); 
    return button; 
}
bool Button::isButtonPressed()
{
    return isPressed;
}