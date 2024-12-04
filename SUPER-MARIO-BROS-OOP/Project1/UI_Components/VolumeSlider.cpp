#include "VolumeSlider.h"

VolumeSlider::VolumeSlider(const sf::Vector2f& size, const sf::Vector2f& position)
{
	bar.setSize(size);
	bar.setPosition(position);
	bar.setOutlineThickness(4);
	bar.setFillColor(sf::Color::Color(230, 230, 238));
	bar.setOutlineColor(sf::Color::Color(43, 46, 79));

	handleTexture = std::make_shared<sf::Texture>();
	if (handleTexture->loadFromFile("UI_Components/UI_Texture_Pack/knob.png"))
	{
		std::cout << "load texture for knob successfully!";
	}

	adjustment.setFillColor(sf::Color::Color(128, 169, 175));
	adjustment.setSize(sf::Vector2f(bar.getSize().x / 2.0, bar.getSize().y));
	adjustment.setPosition(bar.getPosition());

	handle.setTexture(*handleTexture);
	handle.setScale(0.5, 0.5);
	handle.setPosition(bar.getPosition().x + adjustment.getSize().x / 2.0 + handle.getGlobalBounds().width, position.y - 12);
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

void VolumeSlider::handleEvent(const sf::Event& event, const sf::RenderWindow& window, bool isClicked)
{
	float leftBound = bar.getPosition().x;
	float rightBound = bar.getPosition().x + bar.getSize().x;
	if (isClicked == true)
	{
		adjustment.setSize(sf::Vector2f(0,bar.getSize().y));
		handle.setPosition(leftBound - handle.getGlobalBounds().width / 2.0, bar.getPosition().y - 8);
		this->isMute = true;
		this->volume = 0.0;
	}
	else
	{
		this->isMute = false;
	}

	if (this->isMute == false)
	{
		sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && handle.getGlobalBounds().contains(mousePos))
		{
			isDragged = true;

		}
		else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			isDragged = false;
			std::cout << "not changing\n";
		}
		if (isDragged)
		{
			float newHandleX = std::max(leftBound, std::min(mousePos.x, rightBound)); // the min part means that if the pos does not the exceed the right bound it returns the current pos, if it is beyond the bounds, min is now the right bound and it's the return value
			// similar to the min part, max ensure that the if the result is less than the left bound it returns the left bound
			handle.setPosition(newHandleX - handle.getGlobalBounds().width / 2.0, handle.getPosition().y);
			float distance = newHandleX - leftBound;
			adjustment.setSize(sf::Vector2f(distance, bar.getSize().y));
			volume = 100 * distance / bar.getSize().x;
			std::cout << "changing\n";
		}
	}
}

float VolumeSlider::getVolume()
{
	return volume;
}