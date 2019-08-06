#pragma once
#include<glad/glad.h>
#include<string>

//TODO set namespace
class Vector4;

namespace Graphics 
{
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
		unsigned int numLevels;

		TexFilter minOnLevel;
		TexFilter minBetweenLevels;
		TexFilter mag;

		TexWrap s;
		TexWrap t;

		TexConfig();
		TexConfig(unsigned int mipmapNumLevels, TexFilter filterMinOnLevel, TexFilter filterMinBetweenLevels, TexFilter filterMag, TexWrap wrapS, TexWrap wrapT);
	};

	class Texture
	{
	private:
		std::string filepathInternal;
		GLuint textureID;
		int width;
		int height;
		//TODO smaller size?
		unsigned int textureUnit;

	public:
		Texture();
		//TODO make bool for error checking
		void Load(std::string filepath, const TexConfig& config);
		void Load(const void* data, int width, int height, const TexParams& params, const TexConfig& config);

		void Bind(unsigned int texUnit);
		void Unbind();

		void SetBorderColor(const Vector4 color);

		int GetWidth() const;
		int GetHeight() const;
		unsigned int GetTextureUnit() const;
		std::string GetFilePath() const;

		void Unload();
		~Texture();

	private:
		void TexParamsToOpenGL(const TexParams& params, GLenum& internalFormat, GLenum& baseFormat, GLenum& type);
		void TexConfigToOpenGL(const TexConfig& config, GLenum& filterMin, GLenum& filterMag, GLenum& wrapS, GLenum& wrapT);
	};
}

