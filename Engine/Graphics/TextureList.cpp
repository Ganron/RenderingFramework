#include"TextureList.h"
#include"../Math/Math.h"
#include"../Utilities/FileSystem.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

Graphics::TextureList::TextureList()
{
	textures.reserve(MAX_TEXTURES);
	this->LoadFromFile("white.jpg");
}

int Graphics::TextureList::AddTexture(const std::string & texName, int width, int height, const void * data, const TexParams & params, const TexConfig & config)
{
	//TODO handle the case when capacity is full
	textures.emplace_back(texName, width, height, data, params, config);
	return textures.size() - 1;
}

int Graphics::TextureList::LoadFromFile(const std::string & filename, const TexConfig & config)
{
	//TODO handle the case when capacity is full

	std::string fullPath = Filesystem::GetTexturePath(filename);
	if (!Filesystem::IsRegularFile(fullPath))
	{
		return 0;
	}

	std::vector<Texture>::size_type i = 0;
	for (i; i < textures.size(); i++)
	{
		if (textures[i].GetName() == filename)
		{
			return i;
		}
	}

	int localWidth;
	int localHeight;
	int channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(fullPath.c_str(), &localWidth, &localHeight, &channels, 0);

	if (data)
	{
		//TODO find a way to handle different bit depths???
		TexParams params((TexChannels)channels, TexFormat::UI_NORM_8);

		this->AddTexture(filename, localWidth, localHeight, reinterpret_cast<void*>(data), params, config);
	}

	stbi_image_free(data);

	return textures.size() - 1;
}

int Graphics::TextureList::GetNumTextures() const
{
	return textures.size();
}

Graphics::Texture& Graphics::TextureList::GetTexture(int index)
{
	if (index < 0 || index >= (int)textures.size())
	{
		return textures[0];
	}
	else
	{
		return textures[index];
	}
}

//TODO handle the case with duplicate names (make such a case impossible!)
Graphics::Texture& Graphics::TextureList::GetTexture(const std::string & textureName)
{
	std::vector<Texture>::iterator it = textures.begin();
	for (it; it != textures.end(); it++)
	{
		if (it->GetName() == textureName)
		{
			return *it;
		}
	}
	return textures[0];
}

//TODO set default text again?
void Graphics::TextureList::ClearList()
{
	textures.clear();
}

void Graphics::TextureList::ResetList()
{
	ClearList();
	this->LoadFromFile("white.jpg");
}


Graphics::TextureList::~TextureList()
{
	ClearList();
}
