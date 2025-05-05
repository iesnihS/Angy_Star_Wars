#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

#define BG_SPR sf::RectangleShape(sf::Vector2f(C::BG_RES_X, C::BG_RES_Y))


class BgElement
{
public:

	static constexpr float farScrollSpeed = 0.1f;
	static constexpr float dstntScrollSpeed = 100.f;
	static constexpr float closeScrollSpeed = 1000.f;

	sf::RectangleShape spr;
	sf::Vector2f offset;
	float scrollSpeed = 0;

	BgElement(sf::Texture& tex, int layer);

	void SetStartPos(sf::Vector2f startPos);
	void Update(sf::Vector2f playerPos, sf::Vector2f playerVel, int x, int y);
	void Draw(sf::RenderWindow* win);
};

