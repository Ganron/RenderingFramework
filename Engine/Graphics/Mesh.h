#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"Buffer.h"
#include"VertexArrayObject.h"
#include<vector>

namespace Graphics
{
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
		Buffer vbo;
		Buffer veo;
		VertexArrayObject vao;
		unsigned int vertexCount;
		unsigned int indexCount;
		unsigned int matIndex; //TODO remove

	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex, size_t additionalSize = 0);

		void AddAttribBatch(const VertexAttributeBatch& batch, size_t size, const void* data);
		void SetUpMesh();
		unsigned int GetMaterialIndex() const;

		void Draw();

		void Delete();
		~Mesh();
	};
}
