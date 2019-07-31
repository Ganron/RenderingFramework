#include"FileSystem.h"

#include<windows.h>
#include<filesystem>
#include<fstream>

namespace Filesystem
{
	std::string ReadFile(const std::string & filepath)
	{
		std::ifstream file;
		file.open(filepath.c_str(), std::ios::in);
		std::string source = "";
		if (file.is_open())
		{

			file.seekg(0, std::ios::end);
			int length = (int)file.tellg();
			source.resize(length);
			file.seekg(0, std::ios::beg);
			file.read(&source[0], length);
			file.close();
		}
		return source;
	}

	bool IsValidFilePath(const std::string& filepath)
	{
		return std::filesystem::exists(filepath);
	}

	bool IsAbsolute(const std::string & filepath)
	{
		std::filesystem::path path(filepath);
		return path.is_absolute();
	}

	std::string GetExecutableDirectory()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::filesystem::path exePath(buffer);
		return exePath.parent_path().string();
	}

	std::string GetRelative(const std::string& absolutePath)
	{
		return std::filesystem::relative(absolutePath, GetExecutableDirectory()).string();
	}

	std::string GetAbsolute(const std::string& relativePath)
	{
		//TODO think about the unnecessary path-string-path conversion
		std::filesystem::path exePath = GetExecutableDirectory();
		exePath /= relativePath;
		return std::filesystem::canonical(exePath).string();
	}
}