#pragma once
#include"Mesh.h"
#include"Material.h"
#include"Texture.h"
#include"Model.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include<vector>
#include<string>

namespace Graphics
{
	class ResourceManager
	{
	public:
		Graphics::MeshList meshList;
		Graphics::MaterialList matList;
		Graphics::TextureList texList;
		Graphics::ModelList modelList;
	public:
		ResourceManager();
		bool LoadModel(const std::string& filename);
		void FreeResources();
		~ResourceManager();
	private:
		void InitMeshes(const aiScene* assimpScene, int matStartIndex, std::vector<MeshMatPair>& indicesOut);
		void InitMaterials(const aiScene* assimpScene);
	};
}
