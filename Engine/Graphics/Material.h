#pragma once
#include"../Math/Vector3.h"
#include"ShaderProgram.h"
#include<vector>
#include<string>

namespace Graphics
{
	const int MAX_MATERIALS = 100;

	class ResourceManager;

	class Material
	{
	private:
		std::string name;
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;
		float specularExponent;
		std::vector<unsigned int> texIndices; //TODO handle different texture types

	public:
		Material(const std::string& matName, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float specExponent, const std::vector<unsigned int>& textureIndices = std::vector<unsigned int>());

		void AddTexIndex(unsigned int texIndex);
		std::vector<unsigned int>::iterator GetTexIndicesStart();
		std::vector<unsigned int>::iterator GetTexIndicesEnd();
		const Vector3& GetAmbientColor() const;
		const Vector3& GetDiffuseColor() const;
		const Vector3& GetSpecularColor() const;
		const float& GetSpecularExponent() const;
		const std::string& GetName() const;

		void SetAmbientColor(const Vector3& ambient);
		void SetDiffuseColor(const Vector3& diffuse);
		void SetSpecularColor(const Vector3& specular);
		void SetSpecularExponent(float specExponent);
		void SetTexIndices(const std::vector<unsigned int>& indices);

		void Bind(Graphics::ShaderProgram& shaderProgram, Graphics::ResourceManager& resourceManager);
		void Unbind(Graphics::ShaderProgram& shaderProgram, Graphics::ResourceManager& resourceManager);

		~Material();
	};

	class MaterialList
	{
	public:
		MaterialList();
		//Returns index
		int CreateMaterial(const std::string& matName, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float specExponent, const std::vector<unsigned int>& textureIndices = std::vector<unsigned int>());

		Material &operator[](int index);

		int GetNumMaterials() const;
		int GetMatIndex(const std::string& matName) const;
		Graphics::Material& GetMaterial(const std::string& matName);
		std::vector<Material>::iterator GetIteratorStart();
		std::vector<Material>::iterator GetIteratorEnd();

		void ClearList();
		void ResetList();
		~MaterialList();

	private:
		std::vector<Material> materials;
		//Associated texture list?

	private:
		void SetDefaultEntry();

	};
}
