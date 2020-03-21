#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"Buffer.h"
#include"VertexArrayObject.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_MESHES = 100;

	struct Vertex
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoordinates;
		//TODO +tangent/bitangent
		Vertex(const Vector3& pos, const Vector3& normal, const Vector2& texCoords);
		Vertex(const Vector3& pos);
	};

	class Mesh
	{
	private:
		std::string name;
		Buffer vbo;
		Buffer veo;
		VertexArrayObject vao;
		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int matIndex; //TODO remove

	public:
		Mesh(const std::string& meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex);

		unsigned int GetMaterialIndex() const;
		const std::string& GetName() const;

		void Draw();

		void Delete();
		~Mesh();
	};

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
