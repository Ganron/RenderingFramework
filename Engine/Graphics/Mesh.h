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

	public:
		Mesh(const std::string& meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

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
		int CreateMesh(const std::string& meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

		const Graphics::Mesh& operator[](int index) const;

		int GetNumMeshes() const;
		int GetMeshIndex(const std::string& meshName) const;
		const Graphics::Mesh& GetMesh(const std::string& meshName) const;

		void DrawMesh(int index);

		void ClearList();
		void ResetList();

		~MeshList();
	private:
		std::vector<Mesh> meshes;

	private:
		void SetDefaultEntry();
	};
}
