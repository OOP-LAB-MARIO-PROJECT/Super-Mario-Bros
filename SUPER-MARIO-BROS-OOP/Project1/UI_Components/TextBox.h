#ifndef TEXTBOX_H  
#define TEXTBOX_H  

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "../Utils/FontManager.h"

class TextBox {
private:
    sf::RectangleShape box;
    sf::Font font;
    sf::Text text;
    bool isPassword;
    bool isSelected;
    std::string textEntered;

public:
    TextBox(float x, float y, float width, float height, bool isPassword);

    void handleInput(sf::Event event);

    void draw(sf::RenderWindow* window);

    std::string getText() const;

    bool isMouseOver(sf::Vector2i mousePos);

    void setSelected(bool selected);

    bool getSelected();
};

#endif  