#pragma once
#include"../Math/Vector3.h"
#include"../Math/Vector4.h"
#include"ShaderProgram.h"

namespace Graphics
{
	const unsigned int MAX_POINT_LIGHTS = 10;
	const unsigned int MAX_SPOT_LIGHTS = 10;

	const int INDEX_UNIFORM_DIR_LIGHT = 14;

	struct DirectionalLight
	{
		Vector3 direction;
		Vector3 ambientColor;
		Vector3 diffuseColor;
		Vector3 specularColor;
	public:
		void SetInShader(ShaderProgram& program);
		void TurnOff(ShaderProgram& program);
	};

	
	struct PointLight
	{
		Vector4 position;
		Vector3 ambientColor;
		float constCoeff;
		Vector3 diffuseColor;
		float linearCoeff;
		Vector3 specularColor;
		float quadraticCoeff;
	};

	struct SpotLight
	{
		Vector3 position;
		float innerConeAngle;
		Vector3 direction;
		float outerConeAngle;
		Vector3 ambientColor;
		float constCoeff;
		Vector3 diffuseColor;
		float linearCoeff;
		Vector3 specularColor;
		float quadraticCoeff;
	};
}
