#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../Utilities/FileSystem.h"
#include<iostream>
#include "Material.h"

namespace Graphics
{/*
	void Model::Load(const std::string & filepath)
	{
		name = filepath;
		std::cout << filepath << std::endl;
		Assimp::Importer importer;
		const aiScene* assimpScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords);

		if (assimpScene)
		{
			InitMaterials(assimpScene);
			InitNode(assimpScene, assimpScene->mRootNode);
		}//TODO else signal error
		std::cout<<std::endl;
	}

	void Model::InitNode(const aiScene * assimpScene, const aiNode * assimpNode)
	{
		std::cout << "Node name: " << assimpNode->mName.C_Str() << std::endl;
		std::cout << "# Children: " << assimpNode->mNumChildren << std::endl;
		for (unsigned int i = 0; i < assimpNode->mNumMeshes; i++)
		{
			std::cout << "Mesh name: " << assimpScene->mMeshes[assimpNode->mMeshes[i]]->mName.C_Str() << std::endl;
			const aiMesh* assimpMesh = assimpScene->mMeshes[assimpNode->mMeshes[i]];
			InitMesh(assimpScene, assimpMesh);
		}

		for (unsigned int i = 0; i < assimpNode->mNumChildren; i++)
		{
			InitNode(assimpScene, assimpNode->mChildren[i]);
		}
	}

	void Model::InitMesh(const aiScene * assimpScene, const aiMesh * assimpMesh)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		for (unsigned int i = 0; i < assimpMesh->mNumVertices; i++)
		{
			Vector3 position;
			position.x = assimpMesh->mVertices[i].x;
			position.y = assimpMesh->mVertices[i].y;
			position.z = assimpMesh->mVertices[i].z;

			Vector3 normal;
			if (assimpMesh->HasNormals())
			{
				normal.x = assimpMesh->mNormals[i].x;
				normal.y = assimpMesh->mNormals[i].y;
				normal.z = assimpMesh->mNormals[i].z;
			}

			Vector2 texCoords;
			if (assimpMesh->HasTextureCoords(0))
			{
				texCoords.x = (assimpMesh->mTextureCoords[0])[i].x;
				texCoords.y = (assimpMesh->mTextureCoords[0])[i].y;
			}

			vertices.emplace_back(position, normal, texCoords);
		}

		for (unsigned int i = 0; i < assimpMesh->mNumFaces; i++)
		{
			aiFace assimpFace = assimpMesh->mFaces[i];
			for (unsigned int j = 0; j < assimpFace.mNumIndices; j++)
			{
				indices.push_back(assimpFace.mIndices[j]);
			}
		}

		unsigned int index = assimpMesh->mMaterialIndex;
		meshes.emplace_back(assimpMesh->mName.C_Str(), vertices, indices, index);
	}

	void Model::InitMaterials(const aiScene * assimpScene)
	{
		for (unsigned int i = 0; i < assimpScene->mNumMaterials; i++)
		{
			materials.emplace_back(Material());
			Material& currentMat = materials.back();

			const aiMaterial* mat = assimpScene->mMaterials[i];

			for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_DIFFUSE); j++)//TODO handle different types of textures
			{
				aiString path;
				mat->GetTexture(aiTextureType_DIFFUSE, j, &path);

				int index = texList.LoadFromFile(path.data);
				currentMat.AddTexIndex(index);
			}

			if (currentMat.GetIndices().size() == 0)
			{
				currentMat.AddTexIndex(0);
			}

			aiColor3D color(0.0f, 0.0f, 0.0f);
			mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
			currentMat.ambientColor = Vector3(color.r, color.g, color.b);

			mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
			currentMat.diffuseColor = Vector3(color.r, color.g, color.b);

			mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
			currentMat.specularColor = Vector3(color.r, color.g, color.b);

			float shininess = 0.0f;
			mat->Get(AI_MATKEY_SHININESS, shininess);
			currentMat.specularExponent = shininess;
		}
	}

	Model::Model(const std::string& filename, TextureList& texList): texList(texList)
	{
		meshes.reserve(100);
		std::string filepath = Filesystem::GetModelPath(filename);
		if (Filesystem::IsValidFilePath(filepath))
		{
			Load(filepath);
		}//TODO else signal error
	}

	void Model::Draw(Graphics::ShaderProgram& program)
	{
		program.UseProgram();
		unsigned int j = 0;
		for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++, j++)
		{
			const Material material = materials[it->GetMaterialIndex()];
			const std::vector<unsigned int>& indices = material.GetIndices();
			for (std::vector<unsigned int>::size_type i = 0; i < indices.size(); i++)
			{
				texList.GetTexture(indices[i]).Bind(i);
			}

			program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL, 1, &(material.ambientColor));
			program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 1, 1, &(material.diffuseColor));
			program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 2, 1, &(material.specularColor));
			program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 3, 1, &(material.specularExponent));

			it->Draw();

			for (std::vector<unsigned int>::size_type i = 0; i < indices.size(); i++)
			{
				texList.GetTexture(indices[i]).Unbind();
			}
		}
	}

	void Model::DrawMesh(int meshIndex, Graphics::ShaderProgram & program)
	{
		program.UseProgram();
		Mesh& mesh = meshes[Clamp(meshIndex, 0, (int)meshes.size())];
		Material& material = materials[mesh.GetMaterialIndex()];
		const std::vector<unsigned int>& indices = material.GetIndices();
		for (std::vector<unsigned int>::size_type i = 0; i < indices.size(); i++)
		{
			texList.GetTexture(indices[i]).Bind(i);
		}

		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL, 1, &(material.ambientColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 1, 1, &(material.diffuseColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 2, 1, &(material.specularColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 3, 1, &(material.specularExponent));

		mesh.Draw();

		for (std::vector<unsigned int>::size_type i = 0; i < indices.size(); i++)
		{
			texList.GetTexture(indices[i]).Unbind();
		}
	}

	void Model::Delete()
	{
		for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++)
		{
			it->Delete();
		}
	}

	Model::~Model()
	{
		this->Delete();
	}

	void Material::AddTexIndex(unsigned int texIndex)
	{
		texIndices.push_back(texIndex);
	}

	const std::vector<unsigned int>& Material::GetIndices() const
	{
		return texIndices;
	}*/

}

namespace GraphicsTest
{/*
	ModelNode::ModelNode(const std::string & nodeName, int meshIndex, int materialIndex, const Matrix4 & localTransform):name(nodeName), meshIndex(meshIndex),
		materialIndex(materialIndex), locTransform(localTransform)
	{
	}

	void ModelNode::AddChild(ModelNode* node)
	{
		children.push_back(node);
		node->parent = this;
	}

	int ModelNode::GetMeshIndex() const
	{
		return meshIndex;
	}

	void ModelNode::SetMeshIndex(int meshIndex)
	{
		this->meshIndex = meshIndex;
	}

	int ModelNode::GetMaterialIndex() const
	{
		return materialIndex;
	}

	void ModelNode::SetMaterialIndex(int materialIndex)
	{
		this->materialIndex = materialIndex;
	}

	const Matrix4 & ModelNode::GetLocalTransform() const
	{
		return locTransform;
	}

	void ModelNode::SetLocalTransform(const Matrix4 & localTransform)
	{
		this->locTransform = localTransform;
	}

	const std::string & ModelNode::GetName() const
	{
		return name;
	}

	int ModelNode::GetNumChildren() const
	{
		return children.size();
	}

	std::vector<ModelNode*>::iterator ModelNode::GetChildrenStart()
	{
		return children.begin();
	}

	std::vector<ModelNode*>::iterator ModelNode::GetChildrenEnd()
	{
		return children.end();
	}

	ModelNode::~ModelNode()
	{
		std::vector<ModelNode*>::iterator it = children.begin();
		for (it; it != children.end(); it++)
		{
			delete *it;
		}
	}

	ModelList::ModelList()
	{
		models.reserve(MAX_MODELS);
		SetDefaultEntry();
	}

	int ModelList::AddModel(ModelNode * rootNode)
	{
		models.push_back(rootNode);
		return models.size()-1;
	}

	int ModelList::GetNumModels() const
	{
		return models.size();
	}

	ModelNode * ModelList::GetModel(int index)
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

	ModelNode * ModelList::GetModel(const std::string & modelName)
	{
		std::vector<ModelNode*>::iterator it = models.begin();
		for (it; it != models.end(); it++)
		{
			if ((*it)->GetName() == modelName)
			{
				return *it;
			}
		}
		return models[0];
	}

	std::vector<ModelNode*>::iterator ModelList::GetIteratorStart()
	{
		return models.begin();
	}

	std::vector<ModelNode*>::iterator ModelList::GetIteratorEnd()
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
		std::vector<ModelNode*>::iterator it = models.begin();
		for (it; it != models.end(); it++)
		{
			delete *it;
		}
		this->ClearList();
	}

	void ModelList::SetDefaultEntry()
	{
		ModelNode* defaultModel = new ModelNode("Default");
		models.push_back(defaultModel);
	}*/
	MeshMatPair::MeshMatPair(): meshIndex(0), matIndex(0)
	{
	}
	MeshMatPair::MeshMatPair(int meshIndex, int matIndex): meshIndex(meshIndex), matIndex(matIndex)
	{
	}
	MeshGroup::MeshGroup(const std::string & name): name(name)
	{
		meshMatPairs.emplace_back(0, 0);
	}
	MeshGroup::MeshGroup(const std::string& name, const std::vector<MeshMatPair>& pairs):name(name), meshMatPairs(pairs)
	{
	}
	void MeshGroup::AddEntry(int meshIndex, int matIndex)
	{
		meshMatPairs.emplace_back(meshIndex, matIndex);
	}
	const std::string & MeshGroup::GetName() const
	{
		return name;
	}
	std::vector<MeshMatPair>::iterator MeshGroup::GetIteratorStart()
	{
		return meshMatPairs.begin();
	}
	std::vector<MeshMatPair>::iterator MeshGroup::GetIteratorEnd()
	{
		return meshMatPairs.end();
	}
	MeshGroup::~MeshGroup()
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

	int ModelList::GetNumModels() const
	{
		return models.size();
	}

	MeshGroup & ModelList::GetModel(int index)
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

	MeshGroup & ModelList::GetModel(const std::string & modelName)
	{
		std::vector<MeshGroup>::iterator it = models.begin();
		for (it; it != models.end(); it++)
		{
			if (it->GetName() == modelName)
			{
				return *it;
			}
		}
		return models[0];
	}

	std::vector<MeshGroup>::iterator ModelList::GetIteratorStart()
	{
		return models.begin();
	}

	std::vector<MeshGroup>::iterator ModelList::GetIteratorEnd()
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
