#pragma once

#include<string>

namespace Filesystem
{
	std::string ReadFile(const std::string& filepath);

	bool IsValidFilePath(const std::string& filepath);

	bool IsAbsolute(const std::string& filepath);

	std::string GetExecutableDirectory();

	std::string GetRelative(const std::string& absolutePath);

	std::string GetAbsolute(const std::string& relativePath);

}