#include"Mesh.h"
#include"ShaderProgram.h"
#include<glad/glad.h>
#include<iostream>

namespace Graphics
{
	Mesh::Mesh(const std::string& meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) :
		vbo(vertices.size() * sizeof(Vertex), &vertices[0]), veo(indices.size() * sizeof(unsigned int), &indices[0]),
		vertexCount(vertices.size()), indexCount(indices.size()), name(meshName)
	{
		vao.StartNewAttribBatch();
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_POS, 3, DataType::FLOAT, AttribType::FLOAT, 0);
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_NORMAL, 3, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, normal));
		vao.AddAttribToBatch(Graphics::INDEX_ATTRIB_TC, 2, DataType::FLOAT, AttribType::FLOAT, offsetof(Vertex, texCoordinates));

		vao.PrepareAttributes();
		vao.RegisterArrayBuffer(0, vao.GetNumberOfBatches(), vertexCount, 0, &vbo);
		vao.RegisterElementBuffer(&veo);
	}

	const std::string & Mesh::GetName() const
	{
		return name;
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
		this->Delete();
	}

	Vertex::Vertex(const Vector3& pos, const Vector3& normal, const Vector2& texCoords) :position(pos), normal(normal), texCoordinates(texCoords)
	{
	}

	Vertex::Vertex(const Vector3 & pos) : position(pos)
	{
	}
}

Graphics::MeshList::MeshList()
{
	meshes.reserve(MAX_MESHES);

	SetDefaultEntry();
}

int Graphics::MeshList::CreateMesh(const std::string & meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	//TODO handle case when capacity is full
	meshes.emplace_back(meshName, vertices, indices);
	return meshes.size() - 1;
}

const Graphics::Mesh & Graphics::MeshList::operator[](int index) const
{
	if (index < 0 || index >= (int)meshes.size())
	{
		return meshes[0];
	}
	else
	{
		return meshes[index];
	}
}

int Graphics::MeshList::GetNumMeshes() const
{
	return meshes.size();
}

//TODO handle the case with duplicate names (make such a case impossible!)
int Graphics::MeshList::GetMeshIndex(const std::string & meshName) const
{
	int counter = 0;
	std::vector<Mesh>::const_iterator it = meshes.begin();
	for (it; it != meshes.end(); it++,counter++)
	{
		if (it->GetName() == meshName)
		{
			return counter;
		}
	}
	return 0;
}

const Graphics::Mesh & Graphics::MeshList::GetMesh(const std::string & meshName) const
{
	return (*this)[this->GetMeshIndex(meshName)];
}

void Graphics::MeshList::DrawMesh(int index)
{
	meshes[index].Draw();
}

//TODO set default mesh again??
void Graphics::MeshList::ClearList()
{
	meshes.clear();
}

void Graphics::MeshList::ResetList()
{
	ClearList();
	SetDefaultEntry();
}

Graphics::MeshList::~MeshList()
{
	this->ClearList();
}

void Graphics::MeshList::SetDefaultEntry()
{
	//Cube as default mesh

	std::vector<Vector3> positions{
		Vector3(-1.0f, -1.0f, 1.0f),
		Vector3(1.0f, -1.0f, 1.0f),
		Vector3(1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, 1.0f),
		Vector3(-1.0f, 1.0f, -1.0f),
		Vector3(-1.0f, -1.0f, -1.0f),
		Vector3(1.0f, -1.0f, -1.0f),
		Vector3(1.0f, 1.0f, -1.0f),
	};

	std::vector<Vector3> normals{
		Vector3(0.0f, 0.0f, 1.0f),
		Vector3(-1.0f, 0.0f, 0.0f),
		Vector3(0.0f, -1.0f, 0.0f),
		Vector3(1.0f, 0.0f, 0.0f),
		Vector3(0.0f, 0.0f, -1.0f),
		Vector3(0.0f, 1.0f, 0.0f),
	};

	std::vector<Vector2> texCoords{
		Vector2(0.0f, 0.0f),
		Vector2(1.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f)
	};

	std::vector<Graphics::Vertex> vertices{
		{ positions[0], normals[0], texCoords[0] },
		{ positions[1], normals[0], texCoords[1] },
		{ positions[2], normals[0], texCoords[3] },
		{ positions[3], normals[0], texCoords[2] },

		{ positions[0], normals[1], texCoords[1] },
		{ positions[3], normals[1], texCoords[3] },
		{ positions[4], normals[1], texCoords[2] },
		{ positions[5], normals[1], texCoords[0] },

		{ positions[0], normals[2], texCoords[2] },
		{ positions[5], normals[2], texCoords[0] },
		{ positions[6], normals[2], texCoords[1] },
		{ positions[1], normals[2], texCoords[3] },

		{ positions[1], normals[3], texCoords[0] },
		{ positions[6], normals[3], texCoords[1] },
		{ positions[2], normals[3], texCoords[2] },
		{ positions[7], normals[3], texCoords[3] },

		{ positions[6], normals[4], texCoords[0] },
		{ positions[5], normals[4], texCoords[1] },
		{ positions[4], normals[4], texCoords[3] },
		{ positions[7], normals[4], texCoords[2] },

		{ positions[7], normals[5], texCoords[3] },
		{ positions[4], normals[5], texCoords[2] },
		{ positions[2], normals[5], texCoords[1] },
		{ positions[3], normals[5], texCoords[0] },
	};

	std::vector<unsigned int> indices{
		0,1,2, 0,2,3, //front
		4,5,6, 4,6,7, //left
		8,9,10, 8,10,11, //bottom
		12,13,14, 14,13,15, //right
		16,17,18, 16,18,19, //back
		20,21,22, 22,21,23 //top
	};

	meshes.emplace(meshes.begin(), "Default", vertices, indices);
}