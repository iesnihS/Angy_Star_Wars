
#include <imgui.h>
#include <array>
#include <vector>
#include "Entity.hpp"
#include "C.hpp"
#include "Game.hpp"
#include "Tween.h"
#include "HotReloadShader.hpp"
#include "fstream"
#include "Utils.h"
#include "PlanetManager.h"


#define BG_SPR sf::RectangleShape(Vector2f(C::BG_RES_X, C::BG_RES_Y))

static int cols = C::RES_X / C::CELL_SIZE;
static int lastLine = C::RES_Y / C::CELL_SIZE - 1;
Game* Game::instance = 0;

PlanetManager pm;


Game::Game(sf::RenderWindow * win) {

	instance = this;
	this->win = win;

	cam = new Camera();

	//bg = sf::RectangleShape(Vector2f((float)win->getSize().x, (float)win->getSize().y));
	bg = sf::RectangleShape(Vector2f(C::BG_RES_X, C::BG_RES_Y));

	bool isOk = tex.loadFromFile("res/bg_stars.png");
	if (!isOk) {
		printf("ERR : LOAD FAILED\n");
	}

	for (int b = 0; b < 9; ++b)
	{
		sf::RectangleShape bgSpr = BG_SPR;
		bgSpr.setTexture(&tex);
		bgSpr.setSize(sf::Vector2f(C::BG_RES_X, C::BG_RES_Y));
		bgsFar.push_back(bgSpr);
	}
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			int i = x + 1 + (y + 1) * 3;
			bgsFar[i].setPosition(C::BG_RES_X * x, C::BG_RES_Y * y);
		}
	}
	bg.setTexture(&tex);
	bg.setSize(sf::Vector2f(C::BG_RES_X, C::BG_RES_Y));

	bgShader = new HotReloadShader("res/bg.vert", "res/bg.frag");
	
	initMainChar(3,54,0.5f,0.99f);

	cam->SetFollowTarget(ents[0], { 0, 0.f }, {250.f, 250.f });
}

void Game::initMainChar(int cx, int cy, float rx, float ry)
{
	sf::RectangleShape* sprite = new sf::RectangleShape({ C::CELL_SIZE, C::CELL_SIZE * 2 });
	sprite->setFillColor(sf::Color::Cyan);
	sprite->setOutlineColor(sf::Color::Red);
	sprite->setOutlineThickness(2);
	sprite->setOrigin({ C::CELL_SIZE * 0.5f, C::CELL_SIZE * 2 });
	Entity* e = new Entity(sprite, EntityType::Player, 5);

	e->size = C::CELL_SIZE;
	e->ry = ry;
	e->cx = cx;
	e->cy = cy;
	e->rx = rx;
	e->syncPos();
	

	ents.push_back(e);
}

void Game::initEnnemy(int cx, int cy)
{
	sf::RectangleShape* sprite = new sf::RectangleShape({ C::CELL_SIZE, C::CELL_SIZE * 2 });
	sprite->setFillColor(sf::Color::Red);
	sprite->setOrigin({ C::CELL_SIZE * 0.5f, C::CELL_SIZE * 2 });
	Entity* e = new Entity(sprite, EntityType::Enemy, 2);

	e->size = C::CELL_SIZE;
	e->ry = 0.99f;
	e->cx = cx;
	e->cy = cy;
	e->rx = 0.5f;
	e->dv = { 1,0 };
	e->syncPos();


	ents.push_back(e);
}

void Game::processInput(sf::Event ev) {
	if (ev.type == sf::Event::Closed) {
		win->close();
		closing = true;
		return;
	}
	if (ev.type == sf::Event::KeyReleased) {
		
	
	}
}


static double g_time = 0.0;
static double g_tickTimer = 0.0;


void Game::pollInput(double dt) {

	auto& io = ImGui::GetIO();
	if (dt == 0 || io.WantCaptureMouse || io.WantCaptureKeyboard)
	{
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar)
				mainChar->dv.x = 0;
		}
		return;
	}

	if (ents.size()) {
		auto mainChar = ents[0];
		if (mainChar) {
			mainChar->dv = { 0,0 };
		}
	}

	//bool gamePad = sf::Joystick::isConnected(0);
	float lateralSpeed = 8.0;
	float maxSpeed = 40.0;
	
	float x = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
	if (x < -10 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)){
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar) 
				mainChar->dv.x = x < -10 ? x / 100.f : -1;
		}
	}

	if (x > 10 || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar) 
				mainChar->dv.y = -1;
		}
	}

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar)
				mainChar->dv.y =  +1;
		}
	}

	if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar)
				mainChar->dv.x = x > 10 ? x / 100.f : 1;
		}
	}


	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) < -10 || 
		sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Z) > 10 
		|| sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (ents.size()) {
			auto mainChar = ents[0];
			if (mainChar) {
				mainChar->AddBulletBuffer();
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::T)) {

	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
		if (!wasPressed) {
			onSpacePressed();
			wasPressed = true;
		}
	}
	else {
		wasPressed = false;
	}

}

static sf::VertexArray va;
static RenderStates vaRs;
static std::vector<sf::RectangleShape> rects;

int blendModeIndex(sf::BlendMode bm) {
	if (bm == sf::BlendAlpha) return 0;
	if (bm == sf::BlendAdd) return 1;
	if (bm == sf::BlendNone) return 2;
	if (bm == sf::BlendMultiply) return 3;
	return 4;
};

void Game::update(double dt) {
	dt *= dtModifier;
	cSleep = fmax(cSleep-dt, 0);
	dt = cSleep <= 0 ? dt : 0;
	
	pollInput(dt);

	g_time += dt;

	for(int  i = ents.size()-1; i >= 0; i--)
	{
		Entity* e = ents[i];
		e->update(dt);

		if (!e->isDestroy) continue;
		ents.erase(ents.begin() + i);
		delete e;
	}
	sf::Vector2f playerPos = ents[0]->getCooPixel();
	sf::Vector2f playerVel = { ents[0]->dx, ents[0]->dy };
	//sf::Vector2f playerVel = { 10.f, 10.f };
	playerVel *= (float)dt;

	farOffsetPos -= playerVel * farScrollSpeed;
	dstntOffsetPos -= playerVel * dstntScrollSpeed;
	closeOffsetPos -= playerVel * closeScrollSpeed;
	for (int x = -1; x < 2; ++x)
	{
		for (int y = -1; y < 2; ++y)
		{
			int i = x + 1 + (y + 1) * 3;
			sf::Vector2f pos = { (playerPos.x + farOffsetPos.x + C::BG_RES_X / 2) - C::BG_RES_X * x,
						(playerPos.y + farOffsetPos.y + C::BG_RES_Y / 2) - C::BG_RES_Y * y };
			bgsFar[i].setPosition(pos.x, pos.y);
		}
	}

	for (int i = fVFX.size() - 1; i >= 0; i--)
	{
		VFX* e = fVFX[i];
		e->Update(dt);

		if (!e->isDestroy) continue;
		fVFX.erase(fVFX.begin() + i);
		delete e;
	}

	if (bgShader) bgShader->update(dt);

	pm.SetPlayerActiveChuncks(*ents[0]);

	beforeParts.update(dt);
	afterParts.update(dt);

	cam->UpdateCamera(dt, win);
}

 void Game::draw(sf::RenderWindow & win) {
	if (closing) return;

	sf::RenderStates states = sf::RenderStates::Default;
	sf::Shader * sh = &bgShader->sh;
	states.blendMode = sf::BlendAdd;
	states.shader = sh;
	states.texture = &tex;
	sh->setUniform("texture", tex);
	//sh->setUniform("time", g_time);

	//bgsFar[0].setPosition(playerPos.x - C::BG_RES_X/2 , playerPos.y - C::BG_RES_Y/2);
	//win.draw(bgsFar[0], states);

	for (sf::RectangleShape shape : bgsFar) win.draw(shape, states);
	for (sf::RectangleShape shape : bgsDistant) win.draw(shape, states);
	for (sf::RectangleShape shape : bgsClose) win.draw(shape, states);
	// Background draw
	/*for (sf::RectangleShape shape : bgsFar)
	{
		sf::Vector2f pos = shape.getPosition();
		shape.setPosition(pos.x + playerPos.x + (playerVel.x * farScrollSpeed), 
			pos.y + playerPos.y + playerPos.y + (playerVel.y * farScrollSpeed));
		win.draw(shape, states);
	}*/

	beforeParts.draw(win);

	/*for (sf::RectangleShape& r : rects) 
		win.draw(r);*/

	for(auto& e : ents)
	{
		e->draw(win);
	}
	for (auto& vfx : fVFX)
	{
		vfx->Draw(&win);
	}

	for(auto& chunck : pm.activeChunks)
	{
		chunck->draw(win);
	}

	afterParts.draw(win);
}

void Game::onSpacePressed() {
	
}
bool Game::hasCollision(float gridx, float gridy)
{
	return false;
}

vector<Entity*> Game::hasCollisionEntity(Entity*current)
{
	vector<Entity*> touched;
	for(auto& e : ents)
	{
		if (e != current && e->sptr->getGlobalBounds().intersects(current->sptr->getGlobalBounds()))
			touched.push_back(e);
	}
	return touched;
}

void Game::DrawGrid(bool canDraw)
{
	if (!canDraw) return;

	std::vector<sf::Vertex> lines;
	Color color = Color(255, 255, 255, 255/3);
	for(uint32_t i = 0; i < cols; i++)
	{
		lines.push_back({ sf::Vector2f(i*C::CELL_SIZE,0),color });
		lines.push_back({ sf::Vector2f(i * C::CELL_SIZE,	C::RES_Y),color });
	}
	for (uint32_t i = 0; i < lastLine + 2; i++)
	{
		lines.push_back({ sf::Vector2f(0,i * C::CELL_SIZE),color });
		lines.push_back({ sf::Vector2f(C::RES_X,	i * C::CELL_SIZE),color });
	}
	win->draw(lines.data(), lines.size(), sf::PrimitiveType::Lines);
}

sf::Vector2i Game::GetWMousePosition()
{
	return sf::Mouse::getPosition(*win) + Vector2i(win->getView().getCenter() - win->getView().getSize() / 2.f);
}
sf::Vector2i Game::GetSMousePosition()
{
	return sf::Mouse::getPosition(*win);
}

void Game::DrawDebug()
{
	DrawGrid(canDrawGrid);
}



void Game::SleepDT(double sleep)
{
	cSleep = sleep;
}

void Game::im()
{
	using namespace ImGui;


	if (ImGui::CollapsingHeader("Game", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
	{

		if (TreeNodeEx("General", 0)) {
			Checkbox("Can Draw Grid", &canDrawGrid);
			DragFloat("Delta Time Modifier", &dtModifier, 0.1f, 0.f, 5.f);
			if (Button("Stop Time"))
				dtModifier = 0;
			ImGui::SameLine();
			if (Button("Start Time"))
				dtModifier = 1.f;
			TreePop();
		}
		if (TreeNodeEx("Entities")) {
			for (auto e : ents)
			{
				e->im();
			}
			TreePop();
		}
		if (TreeNodeEx("Camera", 0)) {
			cam->im();
			TreePop();
		}
		if (TreeNodeEx("Planets", 0)) {
			pm.im();
			TreePop();
		}
		
	}
}
void Game::ClearEnts(bool pl)
{
	for (int i = ents.size() - 1; i >= 0; i--)
	{
		Entity* e = ents[i];
		
		if (!pl && e->eType == EntityType::Player)
			continue;
		ents.erase(ents.begin() + i);
		delete e;
	}

}

Game::~Game()
{
	delete cam;
}


