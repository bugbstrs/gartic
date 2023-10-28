#include "FileHandler.h"

void FileHandler::Write(FileType fileType, const std::string& data)
{
	if (fileType == FileType::Dictionary)
	{
		throw std::exception("bad access: tried writing in the dictionary file!");
	}
	if (fileType == FileType::Database)
	{
		// TODO: implement writing in the Database
	}
	if (fileType == FileType::LogFile)
	{
		// TODO: implement writing in the LogFile
	}
	throw std::exception("Invalid FileType provided on FileHandler::write");
}

std::string FileHandler::Read(FileType fileType)
{
	if (fileType == FileType::Dictionary)
	{
		std::vector<std::string> dictionaryWords;
		std::ifstream dictionaryFile(Config::dictionaryFilePath);

		for (std::string word; dictionaryFile >> word;)
		{
			dictionaryWords.push_back(word);
		}

		dictionaryFile.close();

		std::random_device randomSeed;
		std::uniform_int_distribution<int> range(0, (int) dictionaryWords.size());

		return dictionaryWords[range(randomSeed)];
	}
	if (fileType == FileType::Database)
	{
		// TODO: implement reading from the Database
	}
	if (fileType == FileType::LogFile)
	{
		// TODO: implement reading from the LogFile
	}
	throw std::exception("Invalid FileType provided on FileHandler::read");
}