#pragma once
#include "Chunck.h"
#include "Entity.hpp"
#include <unordered_map>

struct Vector2iHash {
	std::size_t operator()(const sf::Vector2i& v) const noexcept {
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};

class PlanetManager
{
public:

	sf::Vector2i playerPos = { 343453452,32452345 };
	std::unordered_map<sf::Vector2i, Chunck*, Vector2iHash> chunks;
	void SetPlayerActiveChuncks(Entity& pl);
	Chunck* GetChunck(sf::Vector2i);
	void SetActiveChunck(sf::Vector2i pos);
	std::vector<Chunck*> activeChunks;
	~PlanetManager();
	bool im();
};

