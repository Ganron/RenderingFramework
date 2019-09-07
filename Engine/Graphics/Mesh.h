#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
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
	Vertex(const Vector3& pos);
};

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

class Mesh
{
private:
	Buffer vbo;
	Buffer veo;
	VertexArrayObject vao;
	const Material* material;
	unsigned int vertexCount;
	unsigned int indexCount;

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material* material, size_t additionalSize = 0);

	void AddAttribBatch(const VertexAttributeBatch& batch, size_t size, const void* data);
	void SetUpMesh();
	const Material* GetMaterial() const;

	void Draw();

	void Delete();
	~Mesh();
};
