#include"TextureManager.h"
#include<vector>

Graphics::TextureManager::TextureManager()
{
	textures.reserve(100);
	CreateTexture("white.jpg");
	textures[0].LoadFromFile("white.jpg");
}

int Graphics::TextureManager::CreateTexture(const std::string & name)
{
	std::vector<Graphics::Texture>::size_type index = 0;
	for (index; index < textures.size(); index++)
	{
		if (name == textures[index].GetName())
		{
			return index;
		}
	}
	textures.emplace_back(name);
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
