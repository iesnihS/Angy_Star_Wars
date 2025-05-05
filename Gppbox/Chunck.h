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
	std::vector<std::vector<Planet*>> _planetMap = std::vector<std::vector<Planet*>>(200, std::vector<Planet*>(200,nullptr));
	void draw(sf::RenderWindow& win);
	bool im();
	void to_json(json& j);
	void from_json(const json& j);
};

