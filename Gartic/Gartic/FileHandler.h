#pragma once
import <vector>;
import <fstream>;
import <string>;
import <random>;
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

