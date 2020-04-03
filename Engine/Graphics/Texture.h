#pragma once
#include<glad/glad.h>
#include<string>
#include<vector>

class Vector4;

namespace Graphics 
{
	const int MAX_TEXTURES = 100;

	enum class TexChannels { R = 1, RG = 2, RGB = 3, RGBA = 4 };
	enum class TexFormat {
		UI_NORM_8, UI_NORM_16,
		I_NORM_8, I_NORM_16,
		FLOAT_16, FLOAT_32,
		UINT_8, UINT_16, UINT_32,
		INT_8, INT_16, INT_32
	};

	struct TexParams
	{
		TexChannels channels;
		TexFormat format;

		TexParams(TexChannels numChannels, TexFormat texelDataFormat);
	};

	enum class TexFilter { NEAREST, LINEAR };
	enum class TexWrap { REPEAT, MIRROR, CLAMP_EDGE, CLAMP_BORDER, MIRROR_CLAMP_EDGE };

	struct TexConfig
	{
		TexFilter minOnLevel;
		TexFilter minBetweenLevels;
		TexFilter mag;

		TexWrap s;
		TexWrap t;

		TexConfig();
		TexConfig(TexFilter filterMinOnLevel, TexFilter filterMinBetweenLevels, TexFilter filterMag, TexWrap wrapS, TexWrap wrapT);
	};

	class Texture
	{
	private:
		std::string textureName;
		GLuint textureID;
		int width;
		int height;
		unsigned int textureUnit;

	public:
		Texture(const std::string& texName, int width, int height, const void* data, const TexParams& params, const TexConfig& config);

		void Bind(unsigned int texUnit);
		void Unbind();

		void SetBorderColor(const Vector4& color);

		int GetWidth() const;
		int GetHeight() const;
		unsigned int GetTextureUnit() const;
		const std::string& GetName() const;

		void Delete();
		~Texture();

	private:
		void TexParamsToOpenGL(const TexParams& params, GLenum& internalFormat, GLenum& baseFormat, GLenum& type);
		void TexConfigToOpenGL(const TexConfig& config, GLenum& filterMin, GLenum& filterMag, GLenum& wrapS, GLenum& wrapT);
	};

	class TextureList
	{
	public:
		TextureList();
		//Returns index
		int CreateTexture(const std::string& texName, int width, int height, const void* data, const TexParams& params, const TexConfig& config = TexConfig());
		//Returns index
		int LoadFromFile(const std::string& filename, const TexConfig& = TexConfig());

		Graphics::Texture& operator[](int index);

		int GetNumTextures() const;
		int GetTexIndex(const std::string& textureName) const;
		Graphics::Texture& GetTexture(const std::string& texName);
		std::vector<Graphics::Texture>::iterator GetIteratorStart();
		std::vector<Graphics::Texture>::iterator GetIteratorEnd();

		void ClearList();
		void ResetList();
		~TextureList();
	private:
		std::vector<Texture> textures;
	};
}