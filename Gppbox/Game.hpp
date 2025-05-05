#pragma once

#include <vector>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

#include "sys.hpp"

#include "Particle.hpp"
#include "ParticleMan.hpp"
#include "Camera.h"
#include "VFX.h"
#include "BgElement.h"


using namespace sf;
class Entity;
class HotReloadShader;

enum class BuildMode
{
	None,
	Block,
	Ennemy
};

class Game {
private :
	void DrawGrid(bool canDraw);
	float cSleep = 0; //current Sleep
	
public:
	Camera* cam;
	sf::RenderWindow*				win = nullptr;

	sf::RectangleShape				bg;
	//std::vector <sf::RectangleShape> bgsFar;
	//std::vector <sf::RectangleShape> bgsDistant;
	//std::vector <sf::RectangleShape> bgsClose;
	std::vector <BgElement>				bgsFar;
	std::vector <BgElement>				bgsDistant;
	std::vector <BgElement>				bgsClose;

	HotReloadShader *				bgShader = nullptr;

	sf::Texture						tex;

	bool canDrawGrid = true;
	float dtModifier = 1;
	bool							closing = false;

	float farScrollSpeed = 0.1f;
	float dstntScrollSpeed = 100.f;
	float closeScrollSpeed = 1000.f;
	sf::Vector2f farOffsetPos;
	sf::Vector2f dstntOffsetPos;
	sf::Vector2f closeOffsetPos;

	std::vector<Entity*> ents;
	std::vector<VFX*> fVFX; //Front

	ParticleMan beforeParts;
	ParticleMan afterParts;

	static Game* instance;

	Game(sf::RenderWindow * win);
	~Game();

	void initMainChar(int cx, int cy, float rx, float ry);
	void initEnnemy(int cx, int cy);

	void processInput(sf::Event ev);
	bool wasPressed = false;
	void pollInput(double dt);
	void onSpacePressed();

	float* bloomWidth;
	
	bool hasCollision(float gridx, float gridy);
	vector<Entity*> hasCollisionEntity(Entity* current);
	void update(double dt);
	
	void draw(sf::RenderWindow& win);

	void im();

	void SleepDT(double sleep);
	void DrawDebug();
	void ClearEnts(bool pl = false);//clear player
	sf::Vector2i GetWMousePosition(); //World
	sf::Vector2i GetSMousePosition(); //Screen
};