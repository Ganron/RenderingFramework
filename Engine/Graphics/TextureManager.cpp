#include"TextureManager.h"
#include<vector>
#include<iostream>

/*
Graphics::TextureManager::TextureManager()
{
	textures.reserve(100);
	CreateTextureFromFile("white.jpg");
}

int Graphics::TextureManager::CreateTextureFromFile(const std::string & filename, const TexConfig& config)
{
	std::vector<Graphics::Texture>::size_type index = 0;
	for (index; index < textures.size(); index++)
	{
		if (filename == textures[index].GetName())
		{
			return index;
		}
	}
	textures.emplace_back();
	textures.back().LoadFromFile(filename, config);
	return index;
}

Graphics::Texture & Graphics::TextureManager::GetTexture(int index)
{
	return textures[index];
}

void Graphics::TextureManager::DeleteTextures()
{
	for (std::vector<Graphics::Texture>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		it->Delete();
	}
	textures.clear();
}

int Graphics::TextureManager::GetNumberOfTextures() const
{
	return textures.size();
}
*/