#include"Material.h"

GraphicsTest::Material::Material(const std::string& matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices): ambientColor(ambient), diffuseColor(diffuse),
specularColor(specular), specularExponent(specExponent), texIndices(textureIndices), name(matName)
{
}


void GraphicsTest::Material::AddTexIndex(unsigned int texIndex)
{
	texIndices.push_back(texIndex);
}

const std::vector<unsigned int>& GraphicsTest::Material::GetIndices() const
{
	return texIndices;
}

const Vector3 & GraphicsTest::Material::GetAmbientColor() const
{
	return ambientColor;
}

const Vector3 & GraphicsTest::Material::GetDiffuseColor() const
{
	return diffuseColor;
}

const Vector3 & GraphicsTest::Material::GetSpecularColor() const
{
	return specularColor;
}

const float GraphicsTest::Material::GetSpecularExponent() const
{
	return specularExponent;
}

const std::string & GraphicsTest::Material::GetName() const
{
	return name;
}

void GraphicsTest::Material::SetAmbientColor(const Vector3 & ambient)
{
	ambientColor = ambient;
}

void GraphicsTest::Material::SetDiffuseColor(const Vector3 & diffuse)
{
	diffuseColor = diffuse;
}

void GraphicsTest::Material::SetSpecularColor(const Vector3 & specular)
{
	specularColor = specular;
}

void GraphicsTest::Material::SetSpecularExponent(float specExponent)
{
	specularExponent = specExponent;
}

void GraphicsTest::Material::SetTexIndices(const std::vector<unsigned int>& indices)
{
	texIndices = indices;
}

GraphicsTest::Material::~Material()
{
}
