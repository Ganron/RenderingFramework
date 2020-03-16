#pragma once
#include"../Math/Vector3.h"
#include<vector>
#include<string>

namespace GraphicsTest
{
	class Material
	{
	private:
		std::string name;
		std::vector<unsigned int> texIndices; //TODO handle different texture types
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;
		float specularExponent;

	public:
		Material(const std::string& matName, const Vector3& ambient, const Vector3& diffuse, const Vector3& specular, float specExponent, const std::vector<unsigned int>& textureIndices = std::vector<unsigned int>());

		void AddTexIndex(unsigned int texIndex);
		const std::vector<unsigned int>& GetIndices() const;
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

		~Material();
	};
}
