#include"Mesh.h"
#include"ShaderProgram.h"
#include<glad/glad.h>
#include<iostream>

namespace Graphics
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex) :
		vbo(vertices.size() * sizeof(Vertex)), veo(indices.size() * sizeof(unsigned int), &indices[0]),
		vertexCount(vertices.size()), indexCount(indices.size()), matIndex(matIndex)
	{
		vbo.SetData(0, vertices.size() * sizeof(Vertex), &vertices[0]);

		vao.AddNewAttribBatch();
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_POS, 3, DataType::FLOAT, AttribType::FLOAT, 0);
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_NORMAL, 3, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, normal));
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_TC, 2, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, texCoordinates));

		vao.PrepareAttributes();
		vao.RegisterArrayBuffer(0, vao.GetNumberOfBatches(), vertexCount, 0, &vbo);
		vao.RegisterElementBuffer(&veo);
	}

	unsigned int Mesh::GetMaterialIndex() const
	{
		return matIndex;
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

	Vertex::Vertex(const Vector3 & pos) : position(pos)
	{
	}
}
