export module FileHandler;

import <fstream>;
import <random>;
import <string>;
import <vector>;

import config;
import FileType;

using String = std::string;

export class FileHandler
{
public:
    String Read  (FileType fileType);
    void   Write (FileType fileType, const String& data);
};