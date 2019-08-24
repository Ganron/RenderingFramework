#pragma once
#include"TextureManager.h"
#include<vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

class Mesh;
class Material;
namespace Graphics {
	class Texture;
}

class Model
{
private:
	std::vector<Mesh> meshes; //TODO make use of parent/child relations
	std::vector<Material> materials;
	
	void Load(const std::string& filepath);
	void InitNode(const aiScene* assimpScene, const aiNode* assimpNode);
	void InitMesh(const aiScene* assimpScene, const aiMesh* assimpMesh);
	void InitMaterials(const aiScene* assimpScene);
	
public:
	Model(const std::string& filename);
	void Draw();
	void Delete();
	~Model();
};
