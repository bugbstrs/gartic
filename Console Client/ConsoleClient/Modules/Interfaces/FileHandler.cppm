export module FileHandler;

import <vector>;
import <fstream>;
import <string>;
import <random>;

import config;
import FileType;

using String = std::string;

export class FileHandler
{
public:
	void Write(FileType fileType, const String& data);
	String Read(FileType fileType);
};