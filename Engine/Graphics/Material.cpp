#include"Material.h"

GraphicsTest::Material::Material(const std::string& matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices): ambientColor(ambient), diffuseColor(diffuse),
specularColor(specular), specularExponent(specExponent), texIndices(textureIndices), name(matName)
{
}

void GraphicsTest::Material::AddTexIndex(unsigned int texIndex)
{
	texIndices.push_back(texIndex);
}

std::vector<unsigned int>::const_iterator GraphicsTest::Material::GetTexIndicesStart() const
{
	return texIndices.begin();
}

std::vector<unsigned int>::const_iterator GraphicsTest::Material::GetTexIndicesEnd() const
{
	return texIndices.end();
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

const float& GraphicsTest::Material::GetSpecularExponent() const
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

GraphicsTest::MaterialList::MaterialList()
{
	materials.reserve(MAX_MATERIALS);
	SetDefaultEntry();
}

int GraphicsTest::MaterialList::CreateMaterial(const std::string & matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices)
{
	materials.emplace_back(matName, ambient, diffuse, specular, specExponent, textureIndices);
	return materials.size() - 1;
}

int GraphicsTest::MaterialList::GetNumMaterials() const
{
	return materials.size();
}

GraphicsTest::Material & GraphicsTest::MaterialList::GetMaterial(int index)
{
	if (index < 0 || index >= (int)materials.size())
	{
		return materials[0];
	}
	else
	{
		return materials[index];
	}
}

//TODO handle the case with duplicate names (make such a case impossible!)
GraphicsTest::Material & GraphicsTest::MaterialList::GetMaterial(const std::string & name)
{
	std::vector<GraphicsTest::Material>::iterator it = materials.begin();
	for (it; it != materials.end(); it++)
	{
		if (it->GetName() == name)
		{
			return *it;
		}
	}
	return materials[0];
}

std::vector<GraphicsTest::Material>::iterator GraphicsTest::MaterialList::GetIteratorStart()
{
	return materials.begin();
}

std::vector<GraphicsTest::Material>::iterator GraphicsTest::MaterialList::GetIteratorEnd()
{
	return materials.end();
}

void GraphicsTest::MaterialList::ClearList()
{
	materials.clear();
}

void GraphicsTest::MaterialList::ResetList()
{
	ClearList();
	SetDefaultEntry();
}

GraphicsTest::MaterialList::~MaterialList()
{
	this->ClearList();
}

void GraphicsTest::MaterialList::SetDefaultEntry()
{
	materials.emplace(
		materials.begin(),
		"Default",
		Vector3(1.0f),
		Vector3(1.0f),
		Vector3(1.0f),
		32.0f);
}
