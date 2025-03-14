#include <GLFW/glfw3.h>
#include <unordered_map>
#include "Lib.hpp"
#include "Math.hpp"
#include "bm/Game.hpp"
#include "bm/Sprite.hpp"
#include "bmg/Game.hpp"



bmg::Game::Game()
{
	/*auto texPixel = bm::getPng("bm/res/pixel.png");
	auto texPhi = bm::getPng("bm/res/phi_angry.png");
	auto texGround = bm::getPng("bm/res/ground.png");
	auto texRed = bm::getPng("bm/res/red.png");*/

	Tex texPlayerShip = bm::getPng("bm/res/playerShip.png");
	auto shdr = bm::getSpriteShader();
	auto texSampler = bgfx::createUniform("tex0", bgfx::UniformType::Sampler, 1);

	/*bm::SpriteBatch sprb;
	int nw = 64;
	int nh = 64;
	sprb.reserve(nw * nh);
	sprb.resize(nw * nh);
	for (int y = 0; y < nh; ++y)
	{
		for (int x = 0; x < nw; ++x)
		{
			int idx = x + y * nw;
			sprb.position[idx] = { 0.0f + 16 * 2 * x, 0.0f + 16 * 2 * y };
			sprb.size[idx] = { 16 * 2, 16 * 2 };
			sprb.uv[idx] = { 0, 0, 1, 1 };
			sprb.color[idx] = { 1, 1, 1, 1 };
		}
	}
	sprb.mat = { texGround, texSampler, shdr };
	*/

	bm::Sprite spr;
	spr.pos = { 100,100 };
	spr.pivot = { 0.5,0.5 };
	spr.size = { 64 * 2, 64 * 2 };
	spr.mat = { texPlayerShip, texSampler, shdr };

	//bg = sprb;
	playerShip = spr;
}

void bmg::Game::update(double dt)
{

}

void bmg::Game::draw()
{
	//bg.draw();
	playerShip.draw();
}

// Singleton
static bmg::Game * s_game = 0;
bmg::Game* bmg::Game::get()
{
	if(!s_game) s_game = new bmg::Game();
	return s_game;
}


static std::unordered_map<int, int> prevState;
void bmg::Game::input(GLFWwindow* window, double dt)
{
	auto wasPressed = [](int k ) {
		return prevState.find(k) != prevState.end() && prevState[k] == GLFW_PRESS;
	};
	auto isDown = [=](int k) {
		return glfwGetKey(window,k) == GLFW_PRESS;
	};
	auto justPressed = [=](int k) {
		return !wasPressed(k) && isDown(k);
	};
	auto justReleased = [=](int k) {
		return wasPressed(k) && !isDown(k);
	};

	if (glfwGetKey(window, GLFW_KEY_UP) != 0)
		playerShip.pos.y -= 5 * 60 * dt;
	if (glfwGetKey(window, GLFW_KEY_DOWN) != 0)
		playerShip.pos.y += 5 * 60 * dt;
	if (glfwGetKey(window, GLFW_KEY_LEFT) != 0) 
		playerShip.pos.x -= 5 * 60 * dt;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) != 0)
		playerShip.pos.x += 5 * 60 * dt;

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) 
		trace("pr");
	
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_REPEAT) 
		trace("rep");
	
	if (justPressed( GLFW_KEY_SPACE)) 
		playerShip.flippedX = !playerShip.flippedX;

	for (auto k : { GLFW_KEY_UP ,GLFW_KEY_DOWN,GLFW_KEY_LEFT ,GLFW_KEY_RIGHT,GLFW_KEY_SPACE })
		prevState[k] = glfwGetKey(window, k);
}
