#include "PlanetManager.h"
#include <fstream>

PlanetManager::PlanetManager()
{
	jsonStream = new std::ofstream{"Chunks.json"};
}

void PlanetManager::SetPlayerActiveChuncks(Entity& pl)
{	
	int xCoord = floor(pl.getPosPixelf().x / Chunck::sizePixel);
	int yCoord = floor(pl.getPosPixelf().y / Chunck::sizePixel);

	if (playerPos != sf::Vector2i(xCoord, yCoord))
	{
		playerPos = sf::Vector2i(xCoord, yCoord);
		activeChunks.clear();
		activeChunks.push_back(GetChunck({ xCoord, yCoord }));
		activeChunks.push_back(GetChunck({ xCoord + 1, yCoord }));
		activeChunks.push_back(GetChunck({ xCoord - 1, yCoord }));
		activeChunks.push_back(GetChunck({ xCoord + 1, yCoord - 1 }));
		activeChunks.push_back(GetChunck({ xCoord - 1, yCoord - 1 }));
		activeChunks.push_back(GetChunck({ xCoord + 1, yCoord + 1 }));
		activeChunks.push_back(GetChunck({ xCoord - 1, yCoord + 1 }));
		activeChunks.push_back(GetChunck({ xCoord, yCoord + 1 }));
		activeChunks.push_back(GetChunck({ xCoord, yCoord - 1 }));
	}

	
}

Chunck* PlanetManager::GetChunck(sf::Vector2i pos)
{
	auto it = chunks.find(pos);
	jsonStream->close();

	std::ifstream i("Chunks.json");
	json worldData;
	if (i.good() && i.peek() != std::ifstream::traits_type::eof())
	{
		i >> worldData;
	}
	
	jsonStream->open("Chunks.json", std::ios_base::app);
	
	if (it == chunks.end()) 
	{
		
		Chunck* chunk = new Chunck(pos);
		chunks[pos] = chunk;
		json chunkData;
		chunk->to_json(chunkData);
		*jsonStream << chunkData;
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

	delete jsonStream;
}

bool PlanetManager::im()
{
	for (auto chunck : activeChunks)
	{
		chunck->im();
	}
	return true;
}