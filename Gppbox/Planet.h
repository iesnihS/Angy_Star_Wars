#pragma once

#include <SFML/Graphics.hpp>
#include "./single_include/nlohmann/json.hpp"
using json = nlohmann::json;

class Planet
{
public :
	sf::Color color;
	float size;
	sf::Vector2f pos;
	sf::Shape* sptr = 0; //nullptr
	Planet(sf::Vector2f tPos, float tSize, sf::Color tColor);
	~Planet();
	void draw(sf::RenderWindow& win);
	bool im();
	void to_json(json& j);
	void from_json(const json& j);
};

