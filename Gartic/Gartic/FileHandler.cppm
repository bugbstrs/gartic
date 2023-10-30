export module FileHandler;

import <vector>;
import <fstream>;
import <string>;
import <random>;

import config;

export class FileHandler
{
public:
	enum FileType
	{
		Dictionary,
		Database,
		LogFile
	};

	static void Write(FileType fileType, const std::string& data);
	static std::string Read(FileType fileType);
	FileHandler() = delete;
};