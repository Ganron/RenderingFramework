#pragma once
#include"ShaderProgram.h"
#include"../Math/Vector3.h"
#include"../Math/Matrix4.h"
#include"Texture.h"
#include"Mesh.h"
#include"Material.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_MODELS = 100;

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
	private:
		std::vector<MeshMatPair> meshMatPairs;
	public:
		Model(const std::string& name);
		Model(const std::string& name, const std::vector<MeshMatPair>& pairs);

		const std::string& GetName() const;

		std::vector<MeshMatPair>::const_iterator GetMeshMatPairStart() const;
		std::vector<MeshMatPair>::const_iterator GetMeshMatPairEnd() const;
		int GetMatIndexOfMesh(int meshIndex) const;

		void Draw(Graphics::ShaderProgram& shaderProgram, Graphics::MeshList& meshList, Graphics::MaterialList& matList);
		~Model();
	};

	class ModelList
	{
	public:
		ModelList(MeshList& meshList, MaterialList& matList);

		int CreateModel(const std::string& name, std::vector<MeshMatPair>& pairs);

		const Graphics::Model& operator[](int index) const;

		int GetNumModels() const;
		int GetModelIndex(const std::string& modelName) const;
		const Graphics::Model& GetModel(const std::string& modelName) const;
		
		void DrawModel(int index, Graphics::ShaderProgram& shaderProgram);

		void ClearList();
		void ResetList();

		~ModelList();

	public:
		Graphics::MeshList& meshList;
		Graphics::MaterialList& matList;

	private:
		std::vector<Model> models;

	private:
		void SetDefaultEntry();
	};
}
