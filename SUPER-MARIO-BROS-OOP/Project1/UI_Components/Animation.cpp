#include "Animation.h"
Animation::Animation(std::shared_ptr<sf::Texture> texture,sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	this->texture = std::make_shared<sf::Texture>(*texture);
	totalTime = 0.0f;
	currentImage.x = 0;
	rect.width = 1.0 * texture->getSize().x / imageCount.x;
	rect.height = 1.0 * texture->getSize().y / imageCount.y;
}

void Animation::renderGif(int row, float deltatime)
{
	currentImage.y = row; //initialise the row, 0 means the first row of the sheet, the index of image (currentImage.x) is alrealy intialised to 0 in the currentImage.x 
	totalTime += deltatime;
	if (totalTime >= switchTime)
	{
		totalTime -= switchTime; //decrement to make a smoother animation
		currentImage.x++; // move to the next image

		if (currentImage.x >= imageCount.x) //if the current image index is out of bound
		{
			currentImage.x = 0; //reset the index to 0
		}
	}
	rect.left = currentImage.x * rect.width; // set the left coordinate of the rectangle to the current image index times the width of a single frame, x coordinate
	rect.top = currentImage.y * rect.height; // set the top coordinate of the rectangle to the current row times the height of a single frame, y coordinate
}

Animation Animation::createAnimation(std::shared_ptr<sf::Texture> texture, sf::Vector2u imageCount, float switchTime)
{
	return Animation(texture,imageCount, switchTime);
}

std::shared_ptr<sf::Texture> Animation::getTexture()
{
	return this->texture;
}