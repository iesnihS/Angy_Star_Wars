#pragma once
#include <bgfx/bgfx.h>
#include "Vector.hpp"
#include "Texture.hpp"

namespace engine
{
	class Sprite
	{
	public:
		Vec2f pos = Vec2f(0);
		Vec2f size = Vec2f(32);
		Material mat;

		bool flippedX = false;
		bool flippedY = false;

		Sprite();
		void Draw();
	};

	struct Material
	{
		Texture texture;
		bgfx::UniformHandle sampler;
		bgfx::ProgramHandle shader;
	};
}


