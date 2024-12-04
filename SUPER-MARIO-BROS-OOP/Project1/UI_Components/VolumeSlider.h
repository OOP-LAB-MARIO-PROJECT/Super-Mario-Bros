#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
class VolumeSlider
{
private:
	std::shared_ptr <sf::Texture> handleTexture;
	sf::Sprite handle;
	sf::RectangleShape bar;
	bool isHovered = false;
	bool isDragged = false;
	float volume = 50.0;
	bool isMute = false;
	sf::RectangleShape adjustment;
public:
	VolumeSlider()
	{

	}
	VolumeSlider(const sf::Vector2f& size, const sf::Vector2f& position);
	~VolumeSlider() 
	{};
	float getVolume();
	static VolumeSlider createVolumeSlider(sf::Vector2f barSize, sf::Vector2f barPosition);
	void draw(sf::RenderWindow* window);
	void handleEvent(const sf::Event& event,const sf::RenderWindow& window, bool isMute);
};


