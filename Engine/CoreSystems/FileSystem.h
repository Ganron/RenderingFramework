#pragma once

#include<string>

namespace Filesystem
{
	std::string ReadFile(const std::string& filePath);

	bool IsValidFilePath(const std::string& filePath);

	bool IsAbsolute(const std::string& filePath);

	std::string GetExecutableDirectory();

	std::string GetRelative(const std::string& absolutePath);

	std::string GetAbsolute(const std::string& relativePath);

}