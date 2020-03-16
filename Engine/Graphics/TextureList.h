#pragma once
#include"Texture.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_TEXTURES = 100;

	class TextureList
	{
	public:
		TextureList();
		//Returns index
		int AddTexture(const std::string& texName, int width, int height, const void* data, const TexParams& params, const TexConfig& config = TexConfig());
		//Returns index
		int LoadFromFile(const std::string& filepath, const TexConfig& = TexConfig());

		int GetNumTextures() const;
		Graphics::Texture& GetTexture(int index);
		Graphics::Texture& GetTexture(const std::string& textureName);

		void ClearList();
		void ResetList();
		~TextureList();
	private:
		std::vector<Texture> textures;
	};
}