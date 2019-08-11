#pragma once
#include"../CoreSystems/Math/Vector2.h"
#include"../CoreSystems/Math/Vector3.h"
#include"Buffer.h"
#include"VertexArrayObject.h"
#include<vector>

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 texCoordinates;
	//TODO +tangent/bitangent
	Vertex(const Vector3& pos, const Vector3& normal, const Vector2& texCoords);
};

class Mesh
{
private:
	Buffer vbo;
	Buffer veo;
	VertexArrayObject vao;
	unsigned int vertexCount;
	unsigned int indexCount;
	unsigned int texIndex;
	//TODO textures

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, size_t additionalSize = 0);

	void AddAttribBatch(const VertexAttributeBatch& batch, size_t size, const void* data);
	void SetUpMesh();
	unsigned int GetTexIndex() const;
	void SetTexIndex(unsigned int index);

	void Draw(unsigned int instanceCount);

	void Delete();
	~Mesh();
};
