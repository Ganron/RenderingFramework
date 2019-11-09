#pragma once
#include"TextureManager.h"
#include"ShaderProgram.h"
#include"../Math/Vector3.h"
#include<vector>
#include<string>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

namespace Graphics {
	class Mesh;
	class Texture;

	class Material
	{
	private:
		std::vector<unsigned int> texIndices;
	public:
		void AddTexIndex(unsigned int texIndex);
		const std::vector<unsigned int>& GetIndices() const;
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;
		float specularExponent;
	};

	class Model
	{
	private:
		std::vector<Mesh> meshes; //TODO make use of parent/child relations
		std::vector<Material> materials;
		TextureManager& texManager;

		void Load(const std::string& filepath);
		void InitNode(const aiScene* assimpScene, const aiNode* assimpNode);
		void InitMesh(const aiScene* assimpScene, const aiMesh* assimpMesh);
		void InitMaterials(const aiScene* assimpScene);

	public:
		Model(const std::string& filename, TextureManager& texManager);
		void Draw(Graphics::ShaderProgram& program);
		void DrawMesh(int meshIndex, Graphics::ShaderProgram& program);
		void Delete();
		~Model();
	};

}
