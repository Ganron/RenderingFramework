#pragma once
#include<vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

class Mesh;
namespace Graphics {
	class Texture;
}

class Model
{
private:
	std::vector<Mesh> meshes; //TODO make use of parent/child relations
	std::vector<Graphics::Texture*> textures;
	//std::string filepath;
	void Load(const std::string& filepath);
	void InitNode(const aiScene* assimpScene, const aiNode* assimpNode);
	void InitMesh(const aiScene* assimpScene, const aiMesh* assimpMesh);
	unsigned int GetTexIndex(const std::string& filepath);
	
public:
	Model(const std::string& filepath);
	void Draw(unsigned int instanceCount);
	void Delete();
	~Model();
};
