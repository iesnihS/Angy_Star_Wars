#include "Planet.h"



Planet::Planet(sf::Vector2f tPos, float tsize, sf::Color tcolor) : pos(tPos), color(tcolor), size(tsize)
{
	sptr = new sf::CircleShape(tsize);
	sptr->setOrigin({ tsize ,tsize });
	sptr->setFillColor(tcolor);
	sptr->setPosition(tPos);
}

Planet::~Planet()
{
	delete sptr;
}
void Planet::draw(sf::RenderWindow& win)
{
	
	if (sptr)
		win.draw(*sptr);
}
void Planet::to_json(json& j) 
{
	j["Color"]["r"] = color.r;
	j["Color"]["g"] = color.g;
	j["Color"]["b"] = color.b;
	j["Size"] = size;
	j["Pos"]["x"] = pos.x;
	j["Pos"]["y"] = pos.y;
}

void Planet::from_json(const json& j) {
	color.r = j["Color"]["r"];
	color.g = j["Color"]["g"];
	color.b = j["Color"]["b"];
	size = j["Size"];
	pos.x = j["Pos"]["x"];
	pos.y = j["Pos"]["y"];
}
