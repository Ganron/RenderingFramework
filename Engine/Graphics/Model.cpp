#include"Model.h"
#include"Texture.h"
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
	std::vector<MeshMatPair>::const_iterator Model::GetMeshMatPairStart() const
	{
		return meshMatPairs.begin();
	}
	std::vector<MeshMatPair>::const_iterator Model::GetMeshMatPairEnd() const
	{
		return meshMatPairs.end();
	}

	int Model::GetMatIndexOfMesh(int meshIndex) const
	{
		std::vector<MeshMatPair>::const_iterator it = GetMeshMatPairStart();
		for (it; it != GetMeshMatPairEnd(); it++)
		{
			if (meshIndex == it->meshIndex)
			{
				return it->matIndex;
			}
		}
		return 0;
	}

	void Model::Draw(Graphics::ShaderProgram & shaderProgram, Graphics::MeshList& meshList, Graphics::MaterialList& matList)
	{
		std::vector<MeshMatPair>::const_iterator it = this->GetMeshMatPairStart();
		for (it; it != this->GetMeshMatPairEnd(); it++)
		{
			matList.BindMat(it->matIndex, shaderProgram);
			meshList.DrawMesh(it->meshIndex);
			matList.UnbindMat(it->matIndex, shaderProgram);
		}
	}

	Model::~Model()
	{
		meshMatPairs.clear();
	}

	ModelList::ModelList(MeshList& meshList, MaterialList& matList): meshList(meshList), matList(matList)
	{
		models.reserve(MAX_MODELS);
		SetDefaultEntry();
	}

	int ModelList::CreateModel(const std::string & name, std::vector<MeshMatPair>& pairs)
	{
		models.emplace_back(name, pairs);
		return models.size()-1;
	}

	const Graphics::Model & ModelList::operator[](int index) const
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

	const Graphics::Model & ModelList::GetModel(const std::string & modelName) const
	{
		return (*this)[this->GetModelIndex(modelName)];
	}

	void ModelList::DrawModel(int index, Graphics::ShaderProgram & shaderProgram)
	{
		models[index].Draw(shaderProgram, meshList, matList);
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
