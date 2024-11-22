#include <SFML/Graphics.hpp>
#include "UI_Components/Button.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Button Example");

    
    Button button = Button::createButton(
        sf::Vector2f(200, 100),           
        sf::Vector2f(300, 250),           
        sf::Color::Blue,                
        sf::Color::Green,                 
        sf::Color::Red,                  
        []() { std::cout << "Button clicked!" << std::endl; }, 
        "Click Me",                       
        30,                               
        sf::Color::White);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            button.handleEvent(event, window);
        }

        window.clear();
        button.draw(&window); 
        window.display();
    }

    return 0;
}
