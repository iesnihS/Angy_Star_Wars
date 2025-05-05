#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

class BgElement
{
public:
	sf::Shape* shape;
	sf::Vector2f vel;
	sf::Vector2f lastPos;
};

