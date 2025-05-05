#include "PlanetManager.h"
#include "C.hpp"

void PlanetManager::SetPlayerActiveChuncks(Entity& pl)
{	
	int xCoord = floor(pl.getPosPixelf().x / Chunck::sizePixel);
	int yCoord = floor(pl.getPosPixelf().y / Chunck::sizePixel);

	sf::Vector2i currentCoord = { xCoord,yCoord };
	if(playerPos != currentCoord)
	{
		playerPos = currentCoord;
		activeChunks.clear();
		
		SetActiveChunck(playerPos);
		SetActiveChunck({ xCoord + 1, yCoord });
		SetActiveChunck({ xCoord - 1, yCoord });
		
		SetActiveChunck({ xCoord + 1, yCoord - 1 });
		SetActiveChunck({ xCoord - 1, yCoord - 1 });
		SetActiveChunck({ xCoord + 1, yCoord + 1 });
		
		SetActiveChunck({ xCoord - 1, yCoord + 1 });
		SetActiveChunck({ xCoord, yCoord + 1 });
		SetActiveChunck({ xCoord, yCoord - 1 });
	}
}

void PlanetManager::SetActiveChunck(sf::Vector2i pos)
{
	Chunck* c = GetChunck(pos);
	if(c!= nullptr)
		activeChunks.push_back(c);
}

Chunck* PlanetManager::GetChunck(sf::Vector2i pos)
{
	if (abs(pos.x) > C::LimitChunck || abs(pos.y) > C::LimitChunck)
		return nullptr;
	auto it = chunks.find(pos);
	if (it == chunks.end()) 
	{
		Chunck* chunk = new Chunck(pos);
		chunks[pos] = chunk;
		return chunk;
	}
	return it->second;
}

PlanetManager::~PlanetManager()
{
	for (auto itr = chunks.begin(); itr != chunks.end();)
	{
		delete itr->second; //delete Chunck
		itr = chunks.erase(itr);
	}
}

bool PlanetManager::im()
{
	for (auto chunck : activeChunks)
	{
		chunck->im();
	}
	return true;
}