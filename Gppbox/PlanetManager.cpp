#include "PlanetManager.h"

void PlanetManager::SetPlayerActiveChuncks(Entity& pl)
{	
	int xCoord = floor(pl.getPosPixelf().x / Chunck::sizePixel);
	int yCoord = floor(pl.getPosPixelf().y / Chunck::sizePixel);

	activeChunks.clear();
	activeChunks.push_back(GetChunck({ xCoord, yCoord}));
	activeChunks.push_back(GetChunck({ xCoord + 1, yCoord }));
	activeChunks.push_back(GetChunck({ xCoord - 1, yCoord }));
	activeChunks.push_back(GetChunck({ xCoord + 1, yCoord -1}));
	activeChunks.push_back(GetChunck({ xCoord - 1, yCoord -1}));
	activeChunks.push_back(GetChunck({ xCoord + 1, yCoord + 1 }));
	activeChunks.push_back(GetChunck({ xCoord - 1, yCoord + 1 }));
	activeChunks.push_back(GetChunck({ xCoord, yCoord + 1 }));
	activeChunks.push_back(GetChunck({ xCoord, yCoord - 1 }));
}

Chunck* PlanetManager::GetChunck(sf::Vector2i pos)
{
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