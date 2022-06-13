#include"FileSystem.h"

#include<windows.h>
#include<filesystem>
#include<fstream>

//TODO think about the unnecessary path-string-path conversions
namespace Filesystem
{
	std::string rootDirectory = "";

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

	bool IsRegularFile(const std::string & filepath)
	{
		return std::filesystem::is_regular_file(filepath);
	}

	bool IsAbsolute(const std::string & filepath)
	{
		std::filesystem::path path(filepath);
		return path.is_absolute();
	}

	std::string GetRootDirectory()
	{
		if (rootDirectory == "")
		{
			char buffer[MAX_PATH];
			GetModuleFileName(NULL, buffer, MAX_PATH);
			std::filesystem::path exePath(buffer);
			rootDirectory = exePath.parent_path().parent_path().parent_path().string();
		}
		return rootDirectory;
	}

	std::string GetTexturePath(const std::string& filename)
	{
		std::filesystem::path filepath = "Resources/Textures";
		filepath /= filename;
		return GetAbsolute(filepath.string());
	}

	std::string GetModelPath(const std::string& filename)
	{
		std::filesystem::path filepath = "Resources/Models";
		filepath /= filename;
		return GetAbsolute(filepath.string());
	}

	std::string GetShaderPath(const std::string& filename)
	{
		std::filesystem::path filepath = "Shaders";
		filepath /= filename;
		return GetAbsolute(filepath.string());
	}

	std::string GetRelative(const std::string& absolutePath)
	{
		return std::filesystem::relative(absolutePath, GetRootDirectory()).string();
	}

	std::string GetAbsolute(const std::string& relativePath)
	{
		std::filesystem::path exePath = GetRootDirectory();
		exePath /= relativePath;
		return std::filesystem::canonical(exePath).string();
	}
}