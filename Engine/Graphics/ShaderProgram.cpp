#include"ShaderProgram.h"
#include"../Utilities/FileSystem.h"
#include<iostream>

Graphics::ShaderProgram::ShaderProgram() :programID(0), errorLog("")
{
	for (int i = 0; i < 5; i++)
	{
		shaders[i] = 0;
	}
}

bool Graphics::ShaderProgram::AddShaderFromFile(const std::string & filename, const ShaderType & shaderType)
{
	std::string filepath = Filesystem::GetShaderPath(filename);
	if (!Filesystem::IsValidFilePath(filepath)) return false; //TODO error log?

	std::string source = Filesystem::ReadFile(filepath);

	return AddShaderFromSource(source, shaderType);
}

bool Graphics::ShaderProgram::AddShaderFromSource(const std::string & source, const ShaderType & shaderType)
{
	if(programID == 0) programID = glCreateProgram();

	int index = static_cast<int>(shaderType);
	if (index < 0 || index>4) return false; //TODO error log?

	shaders[index] = glCreateShader(ShaderTypeToOpenGL(shaderType));
	const char* shaderSource = source.c_str();
	glShaderSource(shaders[index], 1, &shaderSource, NULL);
	glCompileShader(shaders[index]);
	
	GLint logLength;
	glGetShaderiv(shaders[index], GL_INFO_LOG_LENGTH, &logLength);
	char* compileLog = new char[logLength];
	glGetShaderInfoLog(shaders[index], logLength, NULL, compileLog);
	errorLog += ShaderTypeToString(shaderType) + " SHADER COMPILATION LOG\n";
	errorLog += compileLog;
	errorLog += "\n";
	delete[] compileLog;

	glAttachShader(programID, shaders[index]);

	GLint compileResult;
	glGetShaderiv(shaders[index], GL_COMPILE_STATUS, &compileResult);
	
	return compileResult;
}

bool Graphics::ShaderProgram::LinkProgram()
{
	glLinkProgram(programID);

	for (int i = 0; i < 5; i++)
	{
		if (shaders[i] != 0)
		{
			glDetachShader(programID, shaders[i]);
			glDeleteShader(shaders[i]);
		}
	}
	
	GLint logLength;
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
	char* compileLog = new char[logLength];
	glGetProgramInfoLog(programID, logLength, NULL, compileLog);
	errorLog += "LINKING LOG\n";
	errorLog += compileLog;
	errorLog += "\n";
	delete[] compileLog;

	GLint linkResult;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkResult);
	return linkResult;
}

void Graphics::ShaderProgram::UseProgram()
{
	glUseProgram(programID);
}

std::string Graphics::ShaderProgram::GetErrorLog() const
{
	return errorLog;
}

void Graphics::ShaderProgram::SetUniform(int index, int count, float * value)
{
	glProgramUniform1fv(programID, index, count, value);
}

void Graphics::ShaderProgram::SetUniform(int index, int count, int * value)
{
	glProgramUniform1iv(programID, index, count, value);
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Vector2 * value)
{
	glProgramUniform2fv(programID, index, count, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Vector3 * value)
{
	glProgramUniform3fv(programID, index, count, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Vector4 * value)
{
	glProgramUniform4fv(programID, index, count, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Matrix2 * value)
{
	glProgramUniformMatrix2fv(programID, index, count, GL_FALSE, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Matrix3 * value)
{
	glProgramUniformMatrix3fv(programID, index, count, GL_FALSE, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::SetUniform(int index, int count, Matrix4 * value)
{
	glProgramUniformMatrix4fv(programID, index, count, GL_FALSE, reinterpret_cast<float*>(value));
}

void Graphics::ShaderProgram::Delete()
{
	glDeleteProgram(programID);
}

Graphics::ShaderProgram::~ShaderProgram()
{
}

GLenum Graphics::ShaderProgram::ShaderTypeToOpenGL(const ShaderType & shaderType)
{
	switch (shaderType)
	{
		case ShaderType::VERTEX: return GL_VERTEX_SHADER;
		case ShaderType::FRAGMENT: return GL_FRAGMENT_SHADER;
		case ShaderType::TESS_CONTROL: return GL_TESS_CONTROL_SHADER;
		case ShaderType::TESS_EVAL: return GL_TESS_EVALUATION_SHADER;
		case ShaderType::GEOMETRY: return GL_GEOMETRY_SHADER;
		default: return GL_INVALID_ENUM;
	}
}

std::string Graphics::ShaderProgram::ShaderTypeToString(const ShaderType & shaderType)
{
	switch (shaderType)
	{
	case ShaderType::VERTEX: return "VERTEX";
	case ShaderType::FRAGMENT: return "FRAGMENT";
	case ShaderType::TESS_CONTROL: return "TESS_CONTROL";
	case ShaderType::TESS_EVAL: return "TESS_EVAL";
	case ShaderType::GEOMETRY: return "GEOMETRY";
	default: return "";
	}
}
