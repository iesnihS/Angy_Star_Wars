#include "Planet.h"



Planet::Planet(sf::Vector2f pos,float size, sf::Color color)
{
	sptr = new sf::CircleShape(size);
	sptr->setOrigin({ size ,size });
	sptr->setFillColor(color);
	sptr->setPosition(pos);
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
