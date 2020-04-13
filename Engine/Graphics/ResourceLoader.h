#pragma once
#include"Model.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include<vector>
#include<string>

namespace Graphics
{
	class ResourceLoader
	{		
	public:
		
		static bool LoadModel(const std::string& filename, ModelList& modelList);
		
	private:
		ResourceLoader();
		~ResourceLoader();
		static void InitMeshes(const aiScene* assimpScene, MeshList& meshList, int matStartIndex, std::vector<MeshMatPair>& indicesOut);
		static void InitMaterials(const aiScene* assimpScene, MaterialList& matList);
	};
}
