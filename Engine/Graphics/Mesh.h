#pragma once
#include"../CoreSystems/Math/Vector2.h"
#include"../CoreSystems/Math/Vector3.h"
#include"Buffer.h"
#include"VertexArrayObject.h"
#include<vector>

struct Vertex
{
	Vector3 position;
	Vector2 texCoordinates;
	Vertex(Vector3 pos, Vector2 texCoords);
	//TODO normals
};

class Mesh
{
private:
	Buffer vbo;
	Buffer veo;
	VertexArrayObject vao;
	unsigned int vertexCount;
	unsigned int indexCount;
	//TODO textures

public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	//TODO allow additional VeretexAttributeBatches to be added

	void Draw(unsigned int instanceCount);

	void Delete();
	~Mesh();
};
