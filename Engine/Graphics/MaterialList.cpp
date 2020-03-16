#include"MaterialList.h"
#include"Material.h"

GraphicsTest::MaterialList::MaterialList()
{
	materials.reserve(MAX_MATERIALS);
	materials.emplace_back(
		"Default",
		Vector3(1.0f),
		Vector3(1.0f),
		Vector3(1.0f),
		32.0f);
}

int GraphicsTest::MaterialList::AddMaterial(const std::string & matName, const Vector3 & ambient, const Vector3 & diffuse, const Vector3 & specular, float specExponent, const std::vector<unsigned int>& textureIndices)
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

void GraphicsTest::MaterialList::ClearList()
{
	materials.clear();
}

GraphicsTest::MaterialList::~MaterialList()
{
	this->ClearList();
}
