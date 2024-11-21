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

    if (isHovered) {
        shape.setFillColor(hoverColor); // Màu khi hover
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            isPressed = true;
            shape.setFillColor(pressedColor); // Màu khi nhấn
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (isPressed && onClick) {
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
void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Hàm để tạo nút
Button Button::createButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& defaultCol, const sf::Color& hoverCol,
    const sf::Color& pressedCol, const std::function<void()>& onClickCallback) {
    Button button(size, position); // Tạo nút
    button.setColors(defaultCol, hoverCol, pressedCol); // Thiết lập màu sắc cho các trạng thái
    button.setOnClick(onClickCallback); // Thiết lập hàm gọi lại
    return button; // Trả về nút đã cấu hình
}
bool Button::isButtonPressed()
{
    return isPressed;
}