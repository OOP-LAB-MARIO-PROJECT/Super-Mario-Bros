#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(const sf::Vector2f& size, const sf::Vector2f& position)
{
	bar.setSize(size);
	bar.setPosition(position);
	bar.setOutlineThickness(7);
	bar.setFillColor(sf::Color::Color(232, 240, 248));
	bar.setOutlineColor(sf::Color::Black);

	handleTexture = std::make_shared<sf::Texture>();
	if (handleTexture->loadFromFile("UI_Components/UI_Texture_Pack/knob.png"))
	{
		std::cout << "load texture for knob successfully!";
	}
	handle.setTexture(*handleTexture);
	handle.setScale(0.3, 0.3);
	handle.setPosition(position.x + handle.getLocalBounds().width / 2.0 + 10, position.y - 8);

	adjustment.setFillColor(sf::Color::Color(168, 224, 248));
	adjustment.setSize(sf::Vector2f(bar.getSize().x / 2.0, bar.getSize().y));
	adjustment.setPosition(bar.getPosition());
}

VolumeSlider VolumeSlider::createVolumeSlider(sf::Vector2f barSize, sf::Vector2f barPosition) 
{
	VolumeSlider slider(barSize, barPosition);
	return slider;
}

void VolumeSlider::draw(sf::RenderWindow* window)
{
	window->draw(bar);
	window->draw(adjustment);
	window->draw(handle);
}

void VolumeSlider::handleEvent(const sf::Event& event, const sf::RenderWindow& window, bool isMute)
{
	float leftBound = bar.getPosition().x;
	float rightBound = bar.getPosition().x + bar.getSize().x;
	if (isMute == true)
	{
		adjustment.setSize(sf::Vector2f(0,bar.getSize().y));
		handle.setPosition(leftBound - handle.getGlobalBounds().width / 2.0, bar.getPosition().y - 8);
		this->volume = 0;
	}
	else
	{
		handle.setPosition(bar.getPosition().x + handle.getLocalBounds().width / 2.0 + 10, bar.getPosition().y - 8);
		adjustment.setSize(sf::Vector2f(bar.getSize().x / 2.0, bar.getSize().y));
		adjustment.setPosition(bar.getPosition());
		this->volume = 50.0;
	}
	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	float newHandleX = std::max(leftBound, std::min(mousePos.x, rightBound)); // the min part means that if the pos does not the exceed the right bound it returns the current pos, if it is beyond the bounds, min is now the right bound and it's the return value
	// similar to the min part, max ensure that the if the result is less than the left bound it returns the left bound
	isHovered = handle.getGlobalBounds().contains(mousePos);
	if (isHovered)
	{
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			isDragged = true;
			
		}
		//else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		//{
		//	isDragged = false;
		//	std::cout << "not changing\n";
		//}
	}

	if (isDragged)
	{
		handle.setPosition(newHandleX - handle.getGlobalBounds().width / 2.0, handle.getPosition().y);
		float distance = newHandleX - leftBound;
		adjustment.setSize(sf::Vector2f(distance, bar.getSize().y));
		volume = 100 * distance / bar.getSize().x;
		std::cout << "changing\n";
	 if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			isDragged = false;
			std::cout << "not changing\n";
		}
	}
}

float VolumeSlider::getVolume()
{
	return volume;
}