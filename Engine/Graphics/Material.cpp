#include"Material.h"
#include"Texture.h"

Graphics::Material::Material(const std::string& matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices): ambientColor(ambient), diffuseColor(diffuse),
specularColor(specular), specularExponent(specExponent), texIndices(textureIndices), name(matName)
{
}

std::vector<unsigned int>::iterator Graphics::Material::GetTexIndicesStart()
{
	return texIndices.begin();
}

std::vector<unsigned int>::iterator Graphics::Material::GetTexIndicesEnd()
{
	return texIndices.end();
}


const Vector3 & Graphics::Material::GetAmbientColor() const
{
	return ambientColor;
}

const Vector3 & Graphics::Material::GetDiffuseColor() const
{
	return diffuseColor;
}

const Vector3 & Graphics::Material::GetSpecularColor() const
{
	return specularColor;
}

const float& Graphics::Material::GetSpecularExponent() const
{
	return specularExponent;
}

const std::string & Graphics::Material::GetName() const
{
	return name;
}

void Graphics::Material::SetAmbientColor(const Vector3 & ambient)
{
	ambientColor = ambient;
}

void Graphics::Material::SetDiffuseColor(const Vector3 & diffuse)
{
	diffuseColor = diffuse;
}

void Graphics::Material::SetSpecularColor(const Vector3 & specular)
{
	specularColor = specular;
}

void Graphics::Material::SetSpecularExponent(float specExponent)
{
	specularExponent = specExponent;
}

void Graphics::Material::SetTexIndices(const std::vector<unsigned int>& indices)
{
	texIndices = indices;
}

void Graphics::Material::Bind(Graphics::ShaderProgram & shaderProgram, Graphics::TextureList & texList)
{
	std::vector<unsigned int>::iterator texIter = this->GetTexIndicesStart();
	int i = 0;
	for (texIter; texIter != this->GetTexIndicesEnd(); texIter++, i++)
	{
		texList.BindTex(*texIter, i);
	}

	shaderProgram.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL, 1, &(ambientColor));
	shaderProgram.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 1, 1, &(diffuseColor));
	shaderProgram.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 2, 1, &(specularColor));
	shaderProgram.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 3, 1, &(specularExponent));
}

void Graphics::Material::Unbind(Graphics::ShaderProgram & shaderProgram, Graphics::TextureList & texList)
{
	std::vector<unsigned int>::iterator texIter = this->GetTexIndicesStart();
	int i = 0;
	for (texIter; texIter != this->GetTexIndicesEnd(); texIter++, i++)
	{
		texList.UnbindTex(*texIter);
	}
}

Graphics::Material::~Material()
{
}

Graphics::MaterialList::MaterialList(Graphics::TextureList& textureList): texList(textureList)
{
	materials.reserve(MAX_MATERIALS);
	SetDefaultEntry();
}

int Graphics::MaterialList::CreateMaterial(const std::string & matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices)
{
	materials.emplace_back(matName, ambient, diffuse, specular, specExponent, textureIndices);
	return materials.size() - 1;
}

const Graphics::Material & Graphics::MaterialList::operator[](int index) const
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

int Graphics::MaterialList::GetNumMaterials() const
{
	return materials.size();
}

//TODO handle the case with duplicate names (make such a case impossible!)
int Graphics::MaterialList::GetMatIndex(const std::string & matName) const
{
	int counter = 0;
	std::vector<Graphics::Material>::const_iterator it = materials.begin();
	for (it; it != materials.end(); it++,counter++)
	{
		if (it->GetName() == matName)
		{
			return counter;
		}
	}
	return 0;
}

const Graphics::Material & Graphics::MaterialList::GetMaterial(const std::string & matName) const
{
	return (*this)[this->GetMatIndex(matName)];
}

void Graphics::MaterialList::BindMat(int index, Graphics::ShaderProgram & shaderProgram)
{
	if (index < 0 || index >= (int)materials.size())
	{
		index = 0;
	}
	materials[index].Bind(shaderProgram, texList);
}

void Graphics::MaterialList::UnbindMat(int index, Graphics::ShaderProgram & shaderProgram)
{
	if (index < 0 || index >= (int)materials.size())
	{
		index = 0;
	}
	materials[index].Unbind(shaderProgram, texList);
}

void Graphics::MaterialList::ClearList()
{
	materials.clear();
}

void Graphics::MaterialList::ResetList()
{
	ClearList();
	SetDefaultEntry();
}

Graphics::MaterialList::~MaterialList()
{
	this->ClearList();
}

void Graphics::MaterialList::SetDefaultEntry()
{
	materials.emplace(
		materials.begin(),
		"Default",
		Vector3(1.0f),
		Vector3(1.0f),
		Vector3(1.0f),
		32.0f);
}
