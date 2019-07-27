#include"Texture.h"
#include"../CoreSystems/Math/Vector4.h"

#include<stb_image.h>

Texture::Texture():filePath(""), textureID(0), width(0), height(0), textureUnit(0)
{
}

void Texture::Load(const char * filepath, const TexConfig & config)
{
	int localWidth;
	int localHeight;
	int channels;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filepath, &localWidth, &localHeight, &channels, 0);

	if (data)
	{
		filePath = filepath;

		//TODO find a way to handle different bit depths???
		TexParams params((TexChannels)channels, UI_NORM_8);

		Load(reinterpret_cast<void*>(data), localWidth, localHeight, params, config);
	}

	stbi_image_free(data);
}

void Texture::Load(const void * data, int width, int height, const TexParams & params, const TexConfig & config)
{
	this->width = width;
	this->height = height;

	GLenum internalFormat;
	GLenum baseFormat;
	GLenum type;
	TexParamsToOpenGL(params, internalFormat, baseFormat, type);

	glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
	glTextureStorage2D(textureID, config.numLevels, internalFormat, width, height);

	glTextureSubImage2D(textureID, 0, 0, 0, width, height, baseFormat, type, data);
	glGenerateTextureMipmap(textureID);

	GLenum filterMin;
	GLenum filterMag;
	GLenum wrapS;
	GLenum wrapT;
	TexConfigToOpenGL(config, filterMin, filterMag, wrapS, wrapT);

	glTextureParameteri(textureID, GL_TEXTURE_MIN_FILTER, filterMin);
	glTextureParameteri(textureID, GL_TEXTURE_MAG_FILTER, filterMag);
	glTextureParameteri(textureID, GL_TEXTURE_WRAP_S, wrapS);
	glTextureParameteri(textureID, GL_TEXTURE_WRAP_T, wrapT);
}

void Texture::Bind(unsigned int texUnit)
{
	textureUnit = texUnit;
	glBindTextureUnit(textureUnit, textureID);
}

void Texture::Unbind()
{
	glBindTextureUnit(textureUnit, 0);
}

void Texture::SetBorderColor(const Vector4 color)
{
	glTextureParameterfv(textureID, GL_TEXTURE_BORDER_COLOR, &color[0]);
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}

unsigned int Texture::GetTextureUnit() const
{
	return textureUnit;
}

const char * Texture::GetFilePath() const
{
	return filePath;
}

void Texture::Unload()
{
	filePath = "";
	glDeleteTextures(1, &textureID);
}

Texture::~Texture()
{
}

void Texture::TexParamsToOpenGL(const TexParams & params, GLenum & internalFormat, GLenum & baseFormat, GLenum & type)
{
	if (params.channels == R)
	{
		baseFormat = GL_RED;

		switch (params.format)
		{
		case UI_NORM_8: internalFormat = GL_R8; type = GL_UNSIGNED_BYTE; break;
		case UI_NORM_16: internalFormat = GL_R16; type = GL_UNSIGNED_SHORT; break;
		case I_NORM_8: internalFormat = GL_R8_SNORM; type = GL_BYTE; break;
		case I_NORM_16: internalFormat = GL_R16_SNORM; type = GL_SHORT; break;
		case FLOAT_16: internalFormat = GL_R16F; type = GL_HALF_FLOAT; break;
		case FLOAT_32: internalFormat = GL_R32F; type = GL_FLOAT; break;
		case UINT_8: internalFormat = GL_R8UI; type = GL_UNSIGNED_BYTE; break;
		case UINT_16: internalFormat = GL_R16UI; type = GL_UNSIGNED_SHORT; break;
		case UINT_32: internalFormat = GL_R32UI; type = GL_UNSIGNED_INT; break;
		case INT_8: internalFormat = GL_R8I; type = GL_BYTE; break;
		case INT_16: internalFormat = GL_R16I; type = GL_SHORT; break;
		case INT_32: internalFormat = GL_R32I; type = GL_INT; break;
		}

		return;
	}

	if (params.channels == RG)
	{
		baseFormat = GL_RG;

		switch (params.format)
		{
		case UI_NORM_8: internalFormat = GL_RG8; type = GL_UNSIGNED_BYTE; break;
		case UI_NORM_16: internalFormat = GL_RG16; type = GL_UNSIGNED_SHORT; break;
		case I_NORM_8: internalFormat = GL_RG8_SNORM; type = GL_BYTE; break;
		case I_NORM_16: internalFormat = GL_RG16_SNORM; type = GL_SHORT; break;
		case FLOAT_16: internalFormat = GL_RG16F; type = GL_HALF_FLOAT; break;
		case FLOAT_32: internalFormat = GL_RG32F; type = GL_FLOAT; break;
		case UINT_8: internalFormat = GL_RG8UI; type = GL_UNSIGNED_BYTE; break;
		case UINT_16: internalFormat = GL_RG16UI; type = GL_UNSIGNED_SHORT; break;
		case UINT_32: internalFormat = GL_RG32UI; type = GL_UNSIGNED_INT; break;
		case INT_8: internalFormat = GL_RG8I; type = GL_BYTE; break;
		case INT_16: internalFormat = GL_RG16I; type = GL_SHORT; break;
		case INT_32: internalFormat = GL_RG32I; type = GL_INT; break;
		}

		return;
	}

	if (params.channels == RGB)
	{
		baseFormat = GL_RGB;

		switch (params.format)
		{
		case UI_NORM_8: internalFormat = GL_RGB8; type = GL_UNSIGNED_BYTE; break;
		case UI_NORM_16: internalFormat = GL_RGB16; type = GL_UNSIGNED_SHORT; break;
		case I_NORM_8: internalFormat = GL_RGB8_SNORM; type = GL_BYTE; break;
		case I_NORM_16: internalFormat = GL_RGB16_SNORM; type = GL_SHORT; break;
		case FLOAT_16: internalFormat = GL_RGB16F; type = GL_HALF_FLOAT; break;
		case FLOAT_32: internalFormat = GL_RGB32F; type = GL_FLOAT; break;
		case UINT_8: internalFormat = GL_RGB8UI; type = GL_UNSIGNED_BYTE; break;
		case UINT_16: internalFormat = GL_RGB16UI; type = GL_UNSIGNED_SHORT; break;
		case UINT_32: internalFormat = GL_RGB32UI; type = GL_UNSIGNED_INT; break;
		case INT_8: internalFormat = GL_RGB8I; type = GL_BYTE; break;
		case INT_16: internalFormat = GL_RGB16I; type = GL_SHORT; break;
		case INT_32: internalFormat = GL_RGB32I; type = GL_INT; break;
		}

		return;
	}

	if (params.channels == RGBA)
	{
		baseFormat = GL_RGBA;

		switch (params.format)
		{
		case UI_NORM_8: internalFormat = GL_RGBA8; type = GL_UNSIGNED_BYTE; break;
		case UI_NORM_16: internalFormat = GL_RGBA16; type = GL_UNSIGNED_SHORT; break;
		case I_NORM_8: internalFormat = GL_RGBA8_SNORM; type = GL_BYTE; break;
		case I_NORM_16: internalFormat = GL_RGBA16_SNORM; type = GL_SHORT; break;
		case FLOAT_16: internalFormat = GL_RGBA16F; type = GL_HALF_FLOAT; break;
		case FLOAT_32: internalFormat = GL_RGBA32F; type = GL_FLOAT; break;
		case UINT_8: internalFormat = GL_RGBA8UI; type = GL_UNSIGNED_BYTE; break;
		case UINT_16: internalFormat = GL_RGBA16UI; type = GL_UNSIGNED_SHORT; break;
		case UINT_32: internalFormat = GL_RGBA32UI; type = GL_UNSIGNED_INT; break;
		case INT_8: internalFormat = GL_RGBA8I; type = GL_BYTE; break;
		case INT_16: internalFormat = GL_RGBA16I; type = GL_SHORT; break;
		case INT_32: internalFormat = GL_RGBA32I; type = GL_INT; break;
		}

		return;
	}
}

void Texture::TexConfigToOpenGL(const TexConfig & config, GLenum & filterMin, GLenum & filterMag, GLenum & wrapS, GLenum & wrapT)
{
	switch (config.minOnLevel)
	{
	case LINEAR:
		{
			if (config.minBetweenLevels == LINEAR) filterMin = GL_LINEAR_MIPMAP_LINEAR;
			else filterMin = GL_LINEAR_MIPMAP_NEAREST;
			break;
		}
	case NEAREST:
		{
			if (config.minBetweenLevels == NEAREST) filterMin = GL_NEAREST_MIPMAP_NEAREST;
			else filterMin = GL_NEAREST_MIPMAP_LINEAR;
			break;
		}
	}

	switch (config.mag)
	{
		case LINEAR: filterMag = GL_LINEAR; break;
		case NEAREST: filterMag = GL_NEAREST; break;
	}

	switch (config.s)
	{
		case CLAMP_EDGE: wrapS = GL_CLAMP_TO_EDGE; break;
		case CLAMP_BORDER: wrapS = GL_CLAMP_TO_BORDER; break;
		case REPEAT: wrapS = GL_REPEAT; break;
		case MIRROR: wrapS = GL_MIRRORED_REPEAT; break;
		case MIRROR_CLAMP_EDGE: wrapS = GL_MIRROR_CLAMP_TO_EDGE; break;
	}

	switch (config.t)
	{
	case CLAMP_EDGE: wrapT = GL_CLAMP_TO_EDGE; break;
	case CLAMP_BORDER: wrapT = GL_CLAMP_TO_BORDER; break;
	case REPEAT: wrapT = GL_REPEAT; break;
	case MIRROR: wrapT = GL_MIRRORED_REPEAT; break;
	case MIRROR_CLAMP_EDGE: wrapT = GL_MIRROR_CLAMP_TO_EDGE; break;
	}
}

TexParams::TexParams(TexChannels numChannels, TexFormat texelDataFormat): channels(numChannels), format(texelDataFormat)
{
}

TexConfig::TexConfig(): numLevels(1), minOnLevel(LINEAR), minBetweenLevels(LINEAR), mag(LINEAR), s(CLAMP_EDGE), t(CLAMP_EDGE)
{
}

TexConfig::TexConfig(unsigned int mipmapNumLevels, TexFilter filterMinOnLevel, TexFilter filterMinBetweenLevels, TexFilter filterMag, TexWrap wrapS, TexWrap wrapT):
	numLevels(mipmapNumLevels), minOnLevel(filterMinOnLevel), minBetweenLevels(filterMinBetweenLevels), mag(filterMag), s(wrapS), t(wrapT)
{
}
