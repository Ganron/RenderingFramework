#pragma once
#include"Mesh.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_MESHES = 100;

	class MeshList
	{
	public:
		MeshList();

		//Returns index
		int AddMesh(const std::string& meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex);

		int GetNumMeshes() const;
		Graphics::Mesh& GetMesh(int index);
		Graphics::Mesh& GetMesh(const std::string& meshName);

		void ClearList();
		void ResetList();
		~MeshList();
	private:
		std::vector<Mesh> meshes;

	private:
		void SetDefaultEntry();
	};
}
