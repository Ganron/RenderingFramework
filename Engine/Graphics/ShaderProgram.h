#pragma once
#include<glad/glad.h>
#include<string>

//TODO set namespace
class Vector2;
class Vector3;
class Vector4;
class Matrix2;
class Matrix3;
class Matrix4;

namespace Graphics 
{
	enum class ShaderType : int { VERTEX = 0, FRAGMENT = 1, TESS_CONTROL = 2, TESS_EVAL = 3, GEOMETRY = 4 };

	class ShaderProgram
	{
	private:
		std::string errorLog;
		GLuint shaders[5];
		GLuint programID;

	public:
		ShaderProgram();

		bool AddShaderFromFile(const std::string& filename, const ShaderType& shaderType);
		bool AddShaderFromSource(const std::string& source, const ShaderType& shaderType);
		bool LinkProgram();
		void UseProgram();

		std::string GetErrorLog() const;

		void SetUniform(int index, int count, const float* value);
		void SetUniform(int index, int count, const int* value);
		void SetUniform(int index, int count, const Vector2* value);
		void SetUniform(int index, int count, const Vector3* value);
		void SetUniform(int index, int count, const Vector4* value);
		void SetUniform(int index, int count, const Matrix2* value);
		void SetUniform(int index, int count, const Matrix3* value);
		void SetUniform(int index, int count, const Matrix4* value);
		

		void Delete();
		~ShaderProgram();

	private:
		GLenum ShaderTypeToOpenGL(const ShaderType& shaderType);
		std::string ShaderTypeToString(const ShaderType& shaderType);
	};
}
