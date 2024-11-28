#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
    sf::Vector2u imageCount; //to calculate to the size of a single sprite in a row and the number of row
    sf::Vector2u currentImage;
    float totalTime;    //the total time since we last changed image
    float switchTime; //the time it takes before switching to another image
public:
    Animation()
    {
		imageCount = sf::Vector2u(0, 0);
		switchTime = 0.0f;
		totalTime = 0.0f;
		currentImage.x = 0;
    }
	Animation(std::shared_ptr<sf::Texture> texture, sf::Vector2u imageCount, float switchTime);
    ~Animation()
    {}
	sf::IntRect rect; //used to display the animation
	void renderGif(int row,float deltatime);
};

