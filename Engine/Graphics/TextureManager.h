#pragma once
#include"Texture.h"
#include<vector>
#include<string>

namespace Graphics
{
	class TextureManager
	{
	private:
		std::vector<Graphics::Texture> textures;
	public:
		TextureManager();
		int CreateTexture(const std::string& name);
		Texture& GetTexture(int index);
		int GetNumberOfTextures() const;
		void DeleteTextures();
	};
}

//TODO make a class