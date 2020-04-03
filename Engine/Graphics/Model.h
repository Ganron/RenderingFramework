#pragma once
#include"ShaderProgram.h"
#include"../Math/Vector3.h"
#include"../Math/Matrix4.h"
#include"Texture.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_MODELS = 100;

	class ResourceManager;
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

	class Model
	{
	public:
		std::string name;
		std::vector<MeshMatPair> meshMatPairs;
	public:
		Model(const std::string& name);
		Model(const std::string& name, const std::vector<MeshMatPair>& pairs);

		void AddEntry(int meshIndex, int matIndex);
		const std::string& GetName() const;

		std::vector<MeshMatPair>::iterator GetIteratorStart();
		std::vector<MeshMatPair>::iterator GetIteratorEnd();
		int GetMatIndexOfMesh(int meshIndex);

		void Draw(Graphics::ShaderProgram& shaderProgram, Graphics::ResourceManager& resourceManager);
		~Model();
	};

	class ModelList
	{
	public:
		ModelList();

		int CreateModel(const std::string& name, std::vector<MeshMatPair>& pairs);

		Graphics::Model& operator[](int index);

		int GetNumModels() const;
		int GetModelIndex(const std::string& modelName) const;
		Graphics::Model& GetModel(const std::string& modelName);
		std::vector<Model>::iterator GetIteratorStart();
		std::vector<Model>::iterator GetIteratorEnd();

		void ClearList();
		void ResetList();

		~ModelList();

	private:
		std::vector<Model> models;

	private:
		void SetDefaultEntry();
	};
}
