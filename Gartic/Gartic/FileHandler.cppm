export module FileHandler;

import <vector>;
import <fstream>;
import <string>;
import <random>;

import config;

using String = std::string;

export class FileHandler
{
public:
	enum FileType
	{
		Dictionary,
		Database,
		LogFile
	};

	static void Write(FileType fileType, const String& data);
	static String Read(FileType fileType);
	
	FileHandler() = delete;
};