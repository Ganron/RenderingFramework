#include"ResourceLoader.h"
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"../Utilities/FileSystem.h"
#include"Model.h"
#include<iostream>


bool Graphics::ResourceLoader::LoadModel(const std::string & filename, ModelList& modelList)
{
	std::string filepath = Filesystem::GetModelPath(filename);
	std::cout << filepath << std::endl;

	if (!Filesystem::IsValidFilePath(filepath))
	{
		return false;
	}

	Assimp::Importer importer;
	const aiScene* assimpScene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_GenUVCoords);

	if (!assimpScene)
	{
		return false;
	}//TODO else signal error

	std::vector<MeshMatPair> indexPairs;

	InitMeshes(assimpScene, modelList.meshList, modelList.matList.GetNumMaterials(), indexPairs);
	InitMaterials(assimpScene, modelList.matList);

	modelList.CreateModel(filename, indexPairs);
	std::cout << std::endl;
	return true;
}


Graphics::ResourceLoader::~ResourceLoader()
{
}

void Graphics::ResourceLoader::InitMeshes(const aiScene* assimpScene, MeshList& meshList, int matStartIndex, std::vector<MeshMatPair>& indicesOut)
{
	indicesOut.clear();

	for (int i = 0; i < (int)assimpScene->mNumMeshes; i++)
	{
		const aiMesh* assimpMesh = assimpScene->mMeshes[i];

		std::string meshName = assimpMesh->mName.C_Str();

		std::vector<Graphics::Vertex> vertices;
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

		unsigned int matIndex = assimpMesh->mMaterialIndex;
		if (matIndex != 0)
		{
			matIndex = matStartIndex + matIndex - 1;
		}
		int meshIndex = meshList.CreateMesh(meshName, vertices, indices, matIndex);
		indicesOut.emplace_back(meshIndex, matIndex);
	}
}

void Graphics::ResourceLoader::InitMaterials(const aiScene* assimpScene, MaterialList& matList)
{
	for (unsigned int i = 1; i < assimpScene->mNumMaterials; i++)
	{
		const aiMaterial* mat = assimpScene->mMaterials[i];
		
		aiString name;
		mat->Get(AI_MATKEY_NAME, name);
		std::string matName = name.data;

		aiColor3D color(0.0f, 0.0f, 0.0f);
		mat->Get(AI_MATKEY_COLOR_AMBIENT, color);
		Vector3 ambientColor = Vector3(color.r, color.g, color.b);

		mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		Vector3 diffuseColor = Vector3(color.r, color.g, color.b);

		mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
		Vector3 specularColor = Vector3(color.r, color.g, color.b);

		float shininess = 0.0f;
		mat->Get(AI_MATKEY_SHININESS, shininess);

		std::vector<unsigned int> texIndices;
		for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_DIFFUSE); j++)//TODO handle different types of textures
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, j, &path);

			int index = matList.texList.LoadFromFile(path.data);
			texIndices.push_back(index);
		}
		if (texIndices.size() == 0)
		{
			texIndices.push_back(0);
		}
		
		matList.CreateMaterial(matName, ambientColor, diffuseColor, specularColor, shininess, texIndices);
	}
}
