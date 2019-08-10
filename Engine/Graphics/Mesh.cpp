#include"Mesh.h"
#include<glad/glad.h>
#include<iostream>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices):
	vbo(vertices.size()*sizeof(Vertex), &vertices[0]), veo(indices.size()*sizeof(unsigned int), &indices[0]), vertexCount(vertices.size()), indexCount(indices.size())
{
	vao.AddNewAttribBatch();
	vao.AddAttribToBatch(0, 3, DataType::FLOAT, AttribType::FLOAT, 0);
	vao.AddAttribToBatch(1, 2, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, texCoordinates));

	vao.PrepareAttributes();
	vao.RegisterArrayBuffer(0, 1, vertexCount, 0, &vbo);
	vao.RegisterElementBuffer(&veo);
}


void Mesh::Draw(unsigned int instanceCount)
{
	vao.Bind();
	glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL, instanceCount);
	vao.Unbind();
}

void Mesh::Delete()
{
	vbo.Delete();
	veo.Delete();
	vao.Delete();
}

Mesh::~Mesh()
{
}

Vertex::Vertex(Vector3 pos, Vector2 texCoords):position(pos), texCoordinates(texCoords)
{
}
