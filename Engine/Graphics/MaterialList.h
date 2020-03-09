#pragma once
#include"../Math/Vector3.h"
#include<vector>
#include<string>

namespace GraphicsTest
{
	const int MAX_MATERIALS = 100;

	class Material;

	class MaterialList
	{
	public:
		MaterialList();
		//Returns index
		int AddMaterial(const std::string& matName, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float specExponent, const std::vector<unsigned int>& textureIndices = std::vector<unsigned int>());

		int GetNumMaterials() const;
		Material& GetMaterial(int index);
		Material& GetMaterial(const std::string& name);

		void ClearList();
		~MaterialList();

	private:
		std::vector<Material> materials;
		
	};
}
