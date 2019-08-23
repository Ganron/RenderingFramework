#pragma once
#include"Texture.h"
#include<string>

namespace Graphics
{
	namespace TextureManager
	{
		int CreateTexture(const std::string& name);
		Graphics::Texture& GetTexture(int index);
		void DeleteTextures();
	}
}