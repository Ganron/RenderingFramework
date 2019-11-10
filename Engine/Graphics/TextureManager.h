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
		int CreateTextureFromFile(const std::string& filename, const TexConfig& config = TexConfig());
		//TODO create texture from data
		Texture& GetTexture(int index);
		int GetNumberOfTextures() const;
		void DeleteTextures();
	};
}

//TODO make a class