#include"Mesh.h"
#include<glad/glad.h>
#include<iostream>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material* material, size_t additionalSize):
	vbo(vertices.size()*sizeof(Vertex) + additionalSize), veo(indices.size()*sizeof(unsigned int), &indices[0]), 
	vertexCount(vertices.size()), indexCount(indices.size()), material(material)
{
	vbo.SetData(0, vertices.size() * sizeof(Vertex), &vertices[0]);

	vao.AddNewAttribBatch();
	vao.AddAttribToBatch(0, 3, DataType::FLOAT, AttribType::FLOAT, 0);
	vao.AddAttribToBatch(1, 3, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, normal));
	vao.AddAttribToBatch(2, 2, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, texCoordinates));
}

void Mesh::AddAttribBatch(const VertexAttributeBatch & batch, size_t size, const void * data)
{
	if (vbo.GetMaxOffset() + size <= vbo.GetSize())
	{
		vao.AddExistingAttribBatch(batch);
		vbo.SetData(vbo.GetMaxOffset(), size, data);
	}//TODO else signal error?
}

void Mesh::SetUpMesh()
{
	vao.PrepareAttributes();
	vao.RegisterArrayBuffer(0, vao.GetNumberOfBatches(), vertexCount, 0, &vbo);
	vao.RegisterElementBuffer(&veo);
}

const Material * Mesh::GetMaterial() const
{
	return material;
}

void Mesh::Draw()
{
	vao.Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
	vao.Unbind();
}

void Mesh::Delete()
{
	vao.UnregisterBuffers();
	vbo.Delete();
	veo.Delete();
	vao.Delete();
}

Mesh::~Mesh()
{
}

Vertex::Vertex(const Vector3& pos, const Vector3& normal, const Vector2& texCoords) :position(pos), normal(normal), texCoordinates(texCoords)
{
}

void Material::AddTexIndex(unsigned int texIndex)
{
	texIndices.push_back(texIndex);
}

const std::vector<unsigned int>& Material::GetIndices() const
{
	return texIndices;
}
