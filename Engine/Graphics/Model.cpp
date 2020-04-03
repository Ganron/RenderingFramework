#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"ResourceManager.h"
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../Utilities/FileSystem.h"
#include<iostream>
#include "Material.h"



namespace Graphics
{
	MeshMatPair::MeshMatPair(): meshIndex(0), matIndex(0)
	{
	}
	MeshMatPair::MeshMatPair(int meshIndex, int matIndex): meshIndex(meshIndex), matIndex(matIndex)
	{
	}
	Model::Model(const std::string & name): name(name)
	{
		meshMatPairs.emplace_back(0, 0);
	}
	Model::Model(const std::string& name, const std::vector<MeshMatPair>& pairs):name(name), meshMatPairs(pairs)
	{
	}
	void Model::AddEntry(int meshIndex, int matIndex)
	{
		meshMatPairs.emplace_back(meshIndex, matIndex);
	}
	const std::string & Model::GetName() const
	{
		return name;
	}
	std::vector<MeshMatPair>::iterator Model::GetIteratorStart()
	{
		return meshMatPairs.begin();
	}
	std::vector<MeshMatPair>::iterator Model::GetIteratorEnd()
	{
		return meshMatPairs.end();
	}

	int Model::GetMatIndexOfMesh(int meshIndex)
	{
		std::vector<MeshMatPair>::iterator it = GetIteratorStart();
		for (it; it != GetIteratorEnd(); it++)
		{
			if (meshIndex == it->meshIndex)
			{
				return it->matIndex;
			}
		}
		return 0;
	}

	void Model::Draw(Graphics::ShaderProgram & shaderProgram, Graphics::ResourceManager& resourceManager)
	{
		std::vector<MeshMatPair>::iterator it = this->GetIteratorStart();
		for (it; it != this->GetIteratorEnd(); it++)
		{
			resourceManager.matList[it->matIndex].Bind(shaderProgram,resourceManager);
			resourceManager.meshList[it->meshIndex].Draw();
			resourceManager.matList[it->matIndex].Unbind(shaderProgram,resourceManager);
		}
	}

	Model::~Model()
	{
		meshMatPairs.clear();
	}

	ModelList::ModelList()
	{
		models.reserve(MAX_MODELS);
		SetDefaultEntry();
	}

	int ModelList::CreateModel(const std::string & name, std::vector<MeshMatPair>& pairs)
	{
		models.emplace_back(name, pairs);
		return models.size()-1;
	}

	Graphics::Model & ModelList::operator[](int index)
	{
		if (index < 0 || index >= (int)models.size())
		{
			return models[0];
		}
		else
		{
			return models[index];
		}
	}

	int ModelList::GetNumModels() const
	{
		return models.size();
	}

	int ModelList::GetModelIndex(const std::string & modelName) const
	{
		int counter = 0;
		std::vector<Model>::const_iterator it = models.begin();
		for (it; it != models.end(); it++, counter++)
		{
			if (it->GetName() == modelName)
			{
				return counter;
			}
		}
		return 0;
	}

	Graphics::Model & ModelList::GetModel(const std::string & modelName)
	{
		return (*this)[this->GetModelIndex(modelName)];
	}

	std::vector<Model>::iterator ModelList::GetIteratorStart()
	{
		return models.begin();
	}

	std::vector<Model>::iterator ModelList::GetIteratorEnd()
	{
		return models.end();
	}

	void ModelList::ClearList()
	{
		models.clear();
	}

	void ModelList::ResetList()
	{
		ClearList();
		SetDefaultEntry();
	}

	ModelList::~ModelList()
	{
		this->ClearList();
	}

	void ModelList::SetDefaultEntry()
	{
		models.emplace(models.begin(), "Default Model");
	}
}
