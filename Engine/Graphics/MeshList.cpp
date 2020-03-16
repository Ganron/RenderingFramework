#include "MeshList.h"

Graphics::MeshList::MeshList()
{
	meshes.reserve(MAX_MESHES);

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

	meshes.emplace_back("Cube", vertices, indices, -1);
}

int Graphics::MeshList::AddMesh(const std::string & meshName, const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex)
{
	//TODO handle case when capacity is full
	meshes.emplace_back(meshName, vertices, indices, matIndex);
	return meshes.size() - 1;
}

int Graphics::MeshList::GetNumMeshes() const
{
	return meshes.size();
}

Graphics::Mesh& Graphics::MeshList::GetMesh(int index)
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

//TODO handle the case with duplicate names (make such a case impossible!)
Graphics::Mesh& Graphics::MeshList::GetMesh(const std::string & meshName)
{
	std::vector<Mesh>::iterator it = meshes.begin();
	for (it; it != meshes.end(); it++)
	{
		if (it->GetName() == meshName)
		{
			return *it;
		}
	}
	return meshes[0];
}

//TODO set default mesh again??
void Graphics::MeshList::ClearList()
{
	meshes.clear();
}

Graphics::MeshList::~MeshList()
{
	this->ClearList();
}
