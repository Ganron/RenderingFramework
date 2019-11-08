#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../Utilities/FileSystem.h"
#include<iostream>

void Model::Load(const std::string & filepath)
{
	Assimp::Importer importer;
	const aiScene* assimpScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals);

	if (assimpScene)
	{
		InitMaterials(assimpScene);
		InitNode(assimpScene, assimpScene->mRootNode);
	}//TODO else signal error
}

void Model::InitNode(const aiScene * assimpScene, const aiNode * assimpNode)
{
	for (unsigned int i = 0; i < assimpNode->mNumMeshes; i++)
	{
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
	meshes.emplace_back(vertices, indices, index); //TODO +additionalSize?
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

			int index = Graphics::TextureManager::CreateTexture(path.data);
			Graphics::TextureManager::GetTexture(index).LoadFromFile(path.data);
			currentMat.AddTexIndex(index);
		}
		
		aiColor3D color(0.0f,0.0f,0.0f);
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

Model::Model(const std::string& filename)
{
	std::string filepath = Filesystem::GetModelPath(filename);
	if (Filesystem::IsValidFilePath(filepath))
	{
		Load(filepath);
		for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++)
		{
			it->SetUpMesh();
		}
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
			Graphics::TextureManager::GetTexture(indices[i]).Bind(i);
		}

		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL, 1, &(material.ambientColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 1, 1, &(material.diffuseColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 2, 1, &(material.specularColor));
		program.SetUniform(Graphics::INDEX_UNIFORM_MATERIAL + 3, 1, &(material.specularExponent));

		it->Draw();
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
}

void Material::AddTexIndex(unsigned int texIndex)
{
	texIndices.push_back(texIndex);
}

const std::vector<unsigned int>& Material::GetIndices() const
{
	return texIndices;
}
