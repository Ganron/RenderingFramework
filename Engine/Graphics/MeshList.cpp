#include "MeshList.h"

Graphics::MeshList::MeshList()
{
	meshes.reserve(MAX_MESHES);

	//Cube as default mesh

	std::vector<Graphics::Vertex> vertices{
	{ Vector3(-1.0f, -1.0f,  1.0f)},
	{ Vector3(1.0f, -1.0f,  1.0f)},
	{ Vector3(1.0f,  1.0f,  1.0f)},
	{ Vector3(-1.0f,  1.0f,  1.0f)},

	{ Vector3(-1.0, -1.0, -1.0) },
	{ Vector3(1.0, -1.0, -1.0) },
	{ Vector3(1.0,  1.0, -1.0) },
	{ Vector3(-1.0,  1.0, -1.0)}
	};

	std::vector<unsigned int> indices{
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
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
	if (index < 0 || index >= meshes.size())
	{
		return meshes[0];
	}
	else
	{
		return meshes[index];
	}
}

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
