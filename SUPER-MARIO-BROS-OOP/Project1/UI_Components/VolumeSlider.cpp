#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(const sf::Vector2f& size, const sf::Vector2f& position)
{
	bar.setSize(size);
	bar.setPosition(position);
	bar.setOutlineThickness(3);
	bar.setOutlineColor(sf::Color::Black);

	handleTexture = std::make_shared<sf::Texture>();
	if (handleTexture->loadFromFile("UI_Components/UI_Texture_Pack/knob.png"))
	{
		std::cout << "load texture for knob successfully!";
	}
	handle.setTexture(*handleTexture);
	handle.setScale(0.3, 0.3);
	handle.setPosition(position.x + handle.getLocalBounds().width / 2.0 + 10, position.y - 5);
}

VolumeSlider VolumeSlider::createVolumeSlider(sf::Vector2f barSize, sf::Vector2f barPosition) 
{
	VolumeSlider slider(barSize, barPosition);
	return slider;
}

void VolumeSlider::draw(sf::RenderWindow* window)
{
	window->draw(bar);
	window->draw(handle);
}

void VolumeSlider::handleEvent(const sf::Event& event, const sf::RenderWindow& window)
{
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	isHovered = handle.getGlobalBounds().contains(mousePos);
	if (isHovered)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			isDragged = true;
			
		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			isDragged = false;
			std::cout << "not changing\n";
		}
	}

	float leftBound = bar.getPosition().x;
	float rightBound = bar.getPosition().x + bar.getSize().x;
	if (isDragged)
	{
		float newHandleX = std::max(leftBound, std::min(mousePos.x, rightBound)); // the min part means that if the pos does not the exceed the right bound it returns the current pos, if it is beyond the bounds, min is now the right bound and it's the return value
																				// similar to the min part, max ensure that the if the result is less than the left bound it returns the left bound
		handle.setPosition(newHandleX - handle.getGlobalBounds().width / 2.0, handle.getPosition().y);
		float distance = newHandleX - leftBound;
		volume = 1.0 * distance / bar.getSize().x;
		std::cout << "changing\n";
	}
}

float VolumeSlider::getVolume()
{
	return volume;
}