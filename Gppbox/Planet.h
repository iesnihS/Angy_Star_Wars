#pragma once

#include <SFML/Graphics.hpp>
class Planet
{
public :
	sf::Shape* sptr = 0; //nullptr
	Planet(sf::Vector2f pos, float size, sf::Color color);
	~Planet();
	void draw(sf::RenderWindow& win);
	bool im();
};

