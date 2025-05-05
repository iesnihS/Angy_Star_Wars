#pragma once
#include "Planet.h"
#include <vector>
class Chunck
{
public :
	static uint32_t size; //grid
	static uint32_t sizePixel; 

	sf::Vector2i pos;
	Chunck(sf::Vector2i tpos);
	~Chunck();
	std::vector<Planet*> _planetMap;
	void draw(sf::RenderWindow& win);
	bool im();
};

