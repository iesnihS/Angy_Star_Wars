#include "Chunck.h"
#include <imgui.h>
#include "C.hpp"
#include <random>

uint32_t Chunck::size = C::RES_X / C::CELL_SIZE;
uint32_t Chunck::sizePixel = (C::RES_X / C::CELL_SIZE)*C::CELL_SIZE;
void Chunck::draw(sf::RenderWindow& win)
{
	for (uint32_t x = 0; x <size; x++)
	{
		for (uint32_t y = 0; y < size; y++)
		{
			if (_planetMap[x][y] != nullptr)
				_planetMap[x][y]->draw(win);
		}
	}
}

Chunck::Chunck(sf::Vector2i tpos) : pos(tpos)
{
	
	for (uint32_t x = 0; x < size; x++)
	{
		for (uint32_t y = 0; y < size; y++)
		{
			
			if(rand()% 10000 == 0) //use 10 000
			{
				sf::Color col = { (sf::Uint8)(rand() % 255),(sf::Uint8)(rand() % 255) ,(sf::Uint8)(rand() % 255) ,255 };
				_planetMap[x][y] = new Planet(
					{(float)pos.x * size * C::CELL_SIZE + x * C::CELL_SIZE , (float)pos.y * size * C::CELL_SIZE + y * C::CELL_SIZE },
					rand() % 200 + 25,
					col);
			}
		}
	}
}

Chunck::~Chunck()
{
	for (uint32_t x = 0; x < size; x++)
	{
		for (uint32_t y = 0; y < size; y++)
		{
			if (_planetMap[x][y] != nullptr)
				delete _planetMap[x][y];
		}
	}
}

bool Chunck::im()
{
	using namespace ImGui;
	SetWindowFontScale(1.1);
	Text("Chunck :");
	SetWindowFontScale(1);
	Value("Pos X", pos.x);
	SameLine();
	Value(" Y", pos.y);
	return true;
}