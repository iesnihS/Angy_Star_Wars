#include "BgElement.h"
#include "C.hpp"

BgElement::BgElement(sf::Texture& tex, int layer)
{
	spr = BG_SPR;
	spr.setTexture(&tex);
	spr.setSize(sf::Vector2f(C::BG_RES_X, C::BG_RES_Y));
	spr.setOrigin(C::BG_RES_X / 2, C::BG_RES_Y / 2);

	switch (layer)
	{
	case 0: scrollSpeed = closeScrollSpeed;
		break;
	case 1: scrollSpeed = dstntScrollSpeed;
		break;
	case 2: scrollSpeed = farScrollSpeed;
		break;
	}
}

void BgElement::SetStartPos(sf::Vector2f startPos)
{
	spr.setPosition(startPos.x, startPos.y);
}

void BgElement::Update(sf::Vector2f playerPos, sf::Vector2f playerVel, int x, int y)
{
	offset -= playerVel * scrollSpeed;

	if (offset.x >= C::BG_RES_X / 2) offset.x = 0;
	if (offset.x <= -C::BG_RES_X / 2) offset.x = C::BG_RES_X;
	if (offset.y >= C::BG_RES_Y / 2) offset.y = 0;
	if (offset.y <= -C::BG_RES_Y / 2) offset.y = C::BG_RES_Y;

	sf::Vector2f pos =
	{
		(playerPos.x + offset.x) - C::BG_RES_X * x,
		(playerPos.y + offset.y) - C::BG_RES_Y * y
	};

	spr.setPosition(pos.x, pos.y);
}

void BgElement::Draw(sf::RenderWindow* win)
{
		win->draw(spr);
}
