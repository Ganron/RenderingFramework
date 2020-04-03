#pragma once
#include"ShaderProgram.h"
#include"../Math/Vector3.h"
#include"../Math/Matrix4.h"
#include"Texture.h"
#include<vector>
#include<string>
/*
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>*/

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
	/*
	//TODO remove class
	class Model
	{
	private:
		std::vector<Mesh> meshes; //TODO make use of parent/child relations
		std::vector<Material> materials;
		TextureList& texList;
		std::string name;

		void Load(const std::string& filepath);
		void InitNode(const aiScene* assimpScene, const aiNode* assimpNode);
		void InitMesh(const aiScene* assimpScene, const aiMesh* assimpMesh);
		void InitMaterials(const aiScene* assimpScene);

	public:
		Model(const std::string& filename, TextureList& texList);
		void Draw(Graphics::ShaderProgram& program);
		void DrawMesh(int meshIndex, Graphics::ShaderProgram& program);
		void Delete();
		~Model();
	};*/

}

namespace GraphicsTest
{
	const int MAX_MODELS = 100;

	class Material;

	struct MeshMatPair
	{
	public:
		MeshMatPair();
		MeshMatPair(int meshIndex, int matIndex);
	public:
		int meshIndex;
		int matIndex;
	};

	class MeshGroup
	{
	public:
		std::string name;
		std::vector<MeshMatPair> meshMatPairs;
	public:
		MeshGroup(const std::string& name);
		MeshGroup(const std::string& name, const std::vector<MeshMatPair>& pairs);
		void AddEntry(int meshIndex, int matIndex);
		const std::string& GetName() const;
		std::vector<MeshMatPair>::iterator GetIteratorStart();
		std::vector<MeshMatPair>::iterator GetIteratorEnd();
		~MeshGroup();
	};

	class ModelList
	{
	public:
		ModelList();

		int CreateModel(const std::string& name, std::vector<MeshMatPair>& pairs);

		int GetNumModels() const;
		MeshGroup& GetModel(int index);
		MeshGroup& GetModel(const std::string& modelName);
		std::vector<MeshGroup>::iterator GetIteratorStart();
		std::vector<MeshGroup>::iterator GetIteratorEnd();

		void ClearList();
		void ResetList();

		~ModelList();

	private:
		std::vector<MeshGroup> models;
		// Associated mesh list and material list?

	private:
		void SetDefaultEntry();
	};
	/*class ModelNode
	{
	private:
		std::string name;
		Matrix4 locTransform;
		int meshIndex;
		int materialIndex;
		ModelNode* parent;
		std::vector<ModelNode*> children;

	public:
		ModelNode(const std::string& nodeName, int meshIndex=-1, int materialIndex=-1, const Matrix4& localTransform=Matrix4());

		void AddChild(ModelNode* node);

		int GetMeshIndex() const;
		void SetMeshIndex(int meshIndex);

		int GetMaterialIndex() const;
		void  SetMaterialIndex(int materialIndex);

		const Matrix4& GetLocalTransform() const;
		void SetLocalTransform(const Matrix4& localTransform);

		const std::string& GetName() const;

		int GetNumChildren() const;
		//TODO total number of descendants
		std::vector<ModelNode*>::iterator GetChildrenStart();
		std::vector<ModelNode*>::iterator GetChildrenEnd();

		~ModelNode();
	};

	class ModelList
	{
	public:
		ModelList();

		int AddModel(ModelNode* rootNode);

		int GetNumModels() const;
		ModelNode* GetModel(int index);
		ModelNode* GetModel(const std::string& modelName);
		std::vector<ModelNode*>::iterator GetIteratorStart();
		std::vector<ModelNode*>::iterator GetIteratorEnd();

		void ClearList();
		void ResetList();

		~ModelList();

	private:
		std::vector<ModelNode*> models;
		// Associated mesh list and material list?

	private:
		void SetDefaultEntry();
	};*/
}
