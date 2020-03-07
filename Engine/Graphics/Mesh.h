#pragma once
#include"../Math/Vector2.h"
#include"../Math/Vector3.h"
#include"Buffer.h"
#include"VertexArrayObject.h"
#include<vector>
#include<string>

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
		std::string name;

	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, unsigned int matIndex, const std::string meshName="");

		unsigned int GetMaterialIndex() const;
		const std::string& GetName() const;

		void Draw();

		void Delete();
		~Mesh();
	};
}
