#pragma once

#include<string>

namespace Filesystem
{
	std::string ReadFile(const std::string& filepath);

	bool IsValidFilePath(const std::string& filepath);

	bool IsRegularFile(const std::string& filepath);

	bool IsAbsolute(const std::string& filepath);

	std::string GetRootDirectory();

	std::string GetTexturePath(const std::string& filename);

	std::string GetModelPath(const std::string& filename);

	std::string GetShaderPath(const std::string& filename);

	std::string GetRelative(const std::string& absolutePath);

	std::string GetAbsolute(const std::string& relativePath);

}