#include"Model.h"
#include"Mesh.h"
#include"Texture.h"
#include"../CoreSystems/Math/Vector2.h"
#include"../CoreSystems/Math/Vector3.h"
#include"../CoreSystems/FileSystem.h"
#include<iostream>

void Model::Load(const std::string & filepath)
{
	Assimp::Importer importer;
	const aiScene* assimpScene = importer.ReadFile(filepath, aiProcess_Triangulate);

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
	meshes.emplace_back(vertices, indices, &materials[index]); //TODO +additionalSize?
}

void Model::InitMaterials(const aiScene * assimpScene)
{
	for (unsigned int i = 0; i < assimpScene->mNumMaterials; i++)
	{
		materials.emplace_back(Material());

		const aiMaterial* mat = assimpScene->mMaterials[i];

		for (unsigned int j = 0; j < mat->GetTextureCount(aiTextureType_DIFFUSE); j++)
		{
			aiString path;
			mat->GetTexture(aiTextureType_DIFFUSE, j, &path);

			textures.push_back(new Graphics::Texture());
			Graphics::TexConfig config(1, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexFilter::LINEAR, Graphics::TexWrap::REPEAT, Graphics::TexWrap::REPEAT);
			textures.back()->Load(path.data, config);

			materials.back().AddTexIndex(textures.size() - 1);
		}
	}
}

Model::Model(const std::string& filepath)
{
	if (Filesystem::IsValidFilePath(filepath))//TODO check relative/absolute
	{
		Load(filepath);
		for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++)
		{
			it->SetUpMesh();
		}
	}//TODO else signal error
}

void Model::Draw()
{
	for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++)
	{
		const std::vector<unsigned int>& indices = it->GetMaterial()->GetIndices();
		for (std::vector<unsigned int>::size_type i = 0; i < indices.size(); i++)
		{
			textures[indices[i]]->Bind(i);
		}
		it->Draw();
	}
}

void Model::Delete()
{
	for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++)
	{
		it->Delete();
	}
	for (std::vector<Graphics::Texture*>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		(*it)->Unload();
		delete (*it);
	}
}

Model::~Model()
{
}
