#include"Lights.h"

namespace Graphics
{
	void DirectionalLight::SetInShader(ShaderProgram & program)
	{
		int used = 1;
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT, 1, &used);
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT + 1, 1, &direction);
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT + 2, 1, &ambientColor);
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT + 3, 1, &diffuseColor);
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT + 4, 1, &specularColor);
	}

	void DirectionalLight::TurnOff(ShaderProgram & program)
	{
		int used = 0;
		program.SetUniform(INDEX_UNIFORM_DIR_LIGHT, 1, &used);
	}
}

