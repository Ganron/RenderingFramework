#include"Texture.h"
#include"../Utilities/FileSystem.h"
#include"../Math/Vector4.h"
#include<iostream>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

namespace Graphics
{
	Texture::Texture(const std::string & texName, int width, int height, const void * data, const TexParams & params, const TexConfig & config)
	{
		textureName = texName;
		
		this->width = width;
		this->height = height;

		GLenum internalFormat;
		GLenum baseFormat;
		GLenum type;
		TexParamsToOpenGL(params, internalFormat, baseFormat, type);

		int levels;
		levels = FloorToInt(Log2((float)Max<int>(width, height))) + 1;

		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		glTextureStorage2D(textureID, levels, internalFormat, width, height);

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

	void Texture::SetBorderColor(const Vector4& color)
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

	const std::string& Texture::GetName() const
	{
		return textureName;
	}

	//TODO decide on obeject deletion method
	void Texture::Delete()
	{
		glDeleteTextures(1, &textureID);
	}

	Texture::~Texture()
	{
		this->Delete();
	}

	void Texture::TexParamsToOpenGL(const TexParams & params, GLenum & internalFormat, GLenum & baseFormat, GLenum & type)
	{
		if (params.channels == TexChannels::R)
		{
			baseFormat = GL_RED;

			switch (params.format)
			{
			case TexFormat::UI_NORM_8: internalFormat = GL_R8; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UI_NORM_16: internalFormat = GL_R16; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::I_NORM_8: internalFormat = GL_R8_SNORM; type = GL_BYTE; break;
			case TexFormat::I_NORM_16: internalFormat = GL_R16_SNORM; type = GL_SHORT; break;
			case TexFormat::FLOAT_16: internalFormat = GL_R16F; type = GL_HALF_FLOAT; break;
			case TexFormat::FLOAT_32: internalFormat = GL_R32F; type = GL_FLOAT; break;
			case TexFormat::UINT_8: internalFormat = GL_R8UI; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UINT_16: internalFormat = GL_R16UI; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::UINT_32: internalFormat = GL_R32UI; type = GL_UNSIGNED_INT; break;
			case TexFormat::INT_8: internalFormat = GL_R8I; type = GL_BYTE; break;
			case TexFormat::INT_16: internalFormat = GL_R16I; type = GL_SHORT; break;
			case TexFormat::INT_32: internalFormat = GL_R32I; type = GL_INT; break;
			default: internalFormat = GL_INVALID_ENUM; type = GL_INVALID_ENUM; break;
			}

			return;
		}

		if (params.channels == TexChannels::RG)
		{
			baseFormat = GL_RG;

			switch (params.format)
			{
			case TexFormat::UI_NORM_8: internalFormat = GL_RG8; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UI_NORM_16: internalFormat = GL_RG16; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::I_NORM_8: internalFormat = GL_RG8_SNORM; type = GL_BYTE; break;
			case TexFormat::I_NORM_16: internalFormat = GL_RG16_SNORM; type = GL_SHORT; break;
			case TexFormat::FLOAT_16: internalFormat = GL_RG16F; type = GL_HALF_FLOAT; break;
			case TexFormat::FLOAT_32: internalFormat = GL_RG32F; type = GL_FLOAT; break;
			case TexFormat::UINT_8: internalFormat = GL_RG8UI; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UINT_16: internalFormat = GL_RG16UI; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::UINT_32: internalFormat = GL_RG32UI; type = GL_UNSIGNED_INT; break;
			case TexFormat::INT_8: internalFormat = GL_RG8I; type = GL_BYTE; break;
			case TexFormat::INT_16: internalFormat = GL_RG16I; type = GL_SHORT; break;
			case TexFormat::INT_32: internalFormat = GL_RG32I; type = GL_INT; break;
			default: internalFormat = GL_INVALID_ENUM; type = GL_INVALID_ENUM; break;
			}

			return;
		}

		if (params.channels == TexChannels::RGB)
		{
			baseFormat = GL_RGB;

			switch (params.format)
			{
			case TexFormat::UI_NORM_8: internalFormat = GL_RGB8; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UI_NORM_16: internalFormat = GL_RGB16; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::I_NORM_8: internalFormat = GL_RGB8_SNORM; type = GL_BYTE; break;
			case TexFormat::I_NORM_16: internalFormat = GL_RGB16_SNORM; type = GL_SHORT; break;
			case TexFormat::FLOAT_16: internalFormat = GL_RGB16F; type = GL_HALF_FLOAT; break;
			case TexFormat::FLOAT_32: internalFormat = GL_RGB32F; type = GL_FLOAT; break;
			case TexFormat::UINT_8: internalFormat = GL_RGB8UI; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UINT_16: internalFormat = GL_RGB16UI; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::UINT_32: internalFormat = GL_RGB32UI; type = GL_UNSIGNED_INT; break;
			case TexFormat::INT_8: internalFormat = GL_RGB8I; type = GL_BYTE; break;
			case TexFormat::INT_16: internalFormat = GL_RGB16I; type = GL_SHORT; break;
			case TexFormat::INT_32: internalFormat = GL_RGB32I; type = GL_INT; break;
			default: internalFormat = GL_INVALID_ENUM; type = GL_INVALID_ENUM; break;
			}

			return;
		}

		if (params.channels == TexChannels::RGBA)
		{
			baseFormat = GL_RGBA;

			switch (params.format)
			{
			case TexFormat::UI_NORM_8: internalFormat = GL_RGBA8; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UI_NORM_16: internalFormat = GL_RGBA16; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::I_NORM_8: internalFormat = GL_RGBA8_SNORM; type = GL_BYTE; break;
			case TexFormat::I_NORM_16: internalFormat = GL_RGBA16_SNORM; type = GL_SHORT; break;
			case TexFormat::FLOAT_16: internalFormat = GL_RGBA16F; type = GL_HALF_FLOAT; break;
			case TexFormat::FLOAT_32: internalFormat = GL_RGBA32F; type = GL_FLOAT; break;
			case TexFormat::UINT_8: internalFormat = GL_RGBA8UI; type = GL_UNSIGNED_BYTE; break;
			case TexFormat::UINT_16: internalFormat = GL_RGBA16UI; type = GL_UNSIGNED_SHORT; break;
			case TexFormat::UINT_32: internalFormat = GL_RGBA32UI; type = GL_UNSIGNED_INT; break;
			case TexFormat::INT_8: internalFormat = GL_RGBA8I; type = GL_BYTE; break;
			case TexFormat::INT_16: internalFormat = GL_RGBA16I; type = GL_SHORT; break;
			case TexFormat::INT_32: internalFormat = GL_RGBA32I; type = GL_INT; break;
			default: internalFormat = GL_INVALID_ENUM; type = GL_INVALID_ENUM; break;
			}

			return;
		}

		internalFormat = GL_INVALID_ENUM;
		baseFormat = GL_INVALID_ENUM;
		type = GL_INVALID_ENUM;
	}

	void Texture::TexConfigToOpenGL(const TexConfig & config, GLenum & filterMin, GLenum & filterMag, GLenum & wrapS, GLenum & wrapT)
	{
		switch (config.minOnLevel)
		{
		case TexFilter::LINEAR:
		{
			if (config.minBetweenLevels == TexFilter::LINEAR) filterMin = GL_LINEAR_MIPMAP_LINEAR;
			else filterMin = GL_LINEAR_MIPMAP_NEAREST;
			break;
		}
		case TexFilter::NEAREST:
		{
			if (config.minBetweenLevels == TexFilter::NEAREST) filterMin = GL_NEAREST_MIPMAP_NEAREST;
			else filterMin = GL_NEAREST_MIPMAP_LINEAR;
			break;
		}
		default: filterMin = GL_INVALID_ENUM; break;
		}

		switch (config.mag)
		{
		case TexFilter::LINEAR: filterMag = GL_LINEAR; break;
		case TexFilter::NEAREST: filterMag = GL_NEAREST; break;
		default: filterMag = GL_INVALID_ENUM; break;
		}

		switch (config.s)
		{
		case TexWrap::CLAMP_EDGE: wrapS = GL_CLAMP_TO_EDGE; break;
		case TexWrap::CLAMP_BORDER: wrapS = GL_CLAMP_TO_BORDER; break;
		case TexWrap::REPEAT: wrapS = GL_REPEAT; break;
		case TexWrap::MIRROR: wrapS = GL_MIRRORED_REPEAT; break;
		case TexWrap::MIRROR_CLAMP_EDGE: wrapS = GL_MIRROR_CLAMP_TO_EDGE; break;
		default: wrapS = GL_INVALID_ENUM; break;
		}

		switch (config.t)
		{
		case TexWrap::CLAMP_EDGE: wrapT = GL_CLAMP_TO_EDGE; break;
		case TexWrap::CLAMP_BORDER: wrapT = GL_CLAMP_TO_BORDER; break;
		case TexWrap::REPEAT: wrapT = GL_REPEAT; break;
		case TexWrap::MIRROR: wrapT = GL_MIRRORED_REPEAT; break;
		case TexWrap::MIRROR_CLAMP_EDGE: wrapT = GL_MIRROR_CLAMP_TO_EDGE; break;
		default: wrapT = GL_INVALID_ENUM; break;
		}
	}

	TexParams::TexParams(TexChannels numChannels, TexFormat texelDataFormat) : channels(numChannels), format(texelDataFormat)
	{
	}

	TexConfig::TexConfig() :minOnLevel(TexFilter::LINEAR), minBetweenLevels(TexFilter::LINEAR), mag(TexFilter::LINEAR), s(TexWrap::REPEAT), t(TexWrap::REPEAT)
	{
	}

	TexConfig::TexConfig(TexFilter filterMinOnLevel, TexFilter filterMinBetweenLevels, TexFilter filterMag, TexWrap wrapS, TexWrap wrapT) :
		minOnLevel(filterMinOnLevel), minBetweenLevels(filterMinBetweenLevels), mag(filterMag), s(wrapS), t(wrapT)
	{
	}
}

Graphics::TextureList::TextureList()
{
	textures.reserve(MAX_TEXTURES);
	this->LoadFromFile("white.jpg");
}

int Graphics::TextureList::CreateTexture(const std::string & texName, int width, int height, const void * data, const TexParams & params, const TexConfig & config)
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

		this->CreateTexture(filename, localWidth, localHeight, reinterpret_cast<void*>(data), params, config);
	}

	stbi_image_free(data);

	return textures.size() - 1;
}

const Graphics::Texture & Graphics::TextureList::operator[](int index) const
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

int Graphics::TextureList::GetNumTextures() const
{
	return textures.size();
}

//TODO handle the case with duplicate names (make such a case impossible!)
int Graphics::TextureList::GetTexIndex(const std::string & textureName) const
{
	int counter = 0;
	std::vector<Texture>::const_iterator it = textures.begin();
	for (it; it != textures.end(); it++,0)
	{
		if (it->GetName() == textureName)
		{
			return counter;
		}
	}
	return 0;
}

const Graphics::Texture & Graphics::TextureList::GetTexture(const std::string & texName)const
{
	return (*this)[this->GetTexIndex(texName)];
}

void Graphics::TextureList::BindTex(int index, int texUnit)
{
	if (index < 0 || index >= (int)textures.size())
	{
		index = 0;
	}
	textures[index].Bind(texUnit);
}

void Graphics::TextureList::UnbindTex(int index)
{
	if (index < 0 || index >= (int)textures.size())
	{
		index = 0;
	}
	textures[index].Unbind();
}

void Graphics::TextureList::SetBorderColorTex(int index, const Vector4 & borderColor)
{
	if (index < 0 || index >= (int)textures.size())
	{
		index = 0;
	}
	textures[index].SetBorderColor(borderColor);
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
