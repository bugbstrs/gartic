#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <random>
import config;

class FileHandler
{
public:
	enum FileType
	{
		Dictionary,
		Database,
		LogFile
	};

	static void write(FileType fileType, const std::string& data);
	static std::string read(FileType fileType);
	FileHandler() = delete;
};

