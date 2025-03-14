#include "Texture.hpp"
#include "Vector.hpp"
using namespace engine;

Texture::Texture(bgfx::TextureHandle _texHdl, Vec2f _size) 
	: texHandle(_texHdl), size(_size){}