#pragma once

#include <bgfx/bgfx.h>
#include "Vector.hpp"

namespace engine
{
	class Texture
	{
		bgfx::TextureHandle texHandle;
		Vec2f size;

		Texture() : size{ 0,0 } {};
		Texture(bgfx::TextureHandle _texHdl, Vec2f _size);
	};
}
