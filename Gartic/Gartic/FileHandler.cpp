module FileHandler;

import <vector>;
import <fstream>;
import <string>;
import <random>;

import config;

void FileHandler::Write(FileType fileType, const String& data)
{
	switch(fileType)
	{
	case FileType::Dictionary:
		throw std::exception("bad access: tried writing in the dictionary file!");
	case FileType::Database:
		// TODO: implement writing in the Database
		break;
	case FileType::LogFile:
		// TODO: implement writing in the LogFile
		break;
	default:
		throw std::exception("Invalid FileType provided on FileHandler::write");
	}

	// TODO: change to custom exceptions
}

String FileHandler::Read(FileType fileType)
{
	switch (fileType)
	{
	case FileType::Dictionary:
	{
		std::vector<String> dictionaryWords;
		std::ifstream dictionaryFile{ Config::dictionaryFilePath };

		for (String word; dictionaryFile >> word;)
		{
			dictionaryWords.push_back(word);
		}

		dictionaryFile.close();

		std::random_device randomSeed;
		std::uniform_int_distribution<int> range{ 0, (int)dictionaryWords.size() };

		return dictionaryWords[range(randomSeed)];
	}
	case FileType::Database:
		// TODO: implement reading in the Database
		break;
	case FileType::LogFile:
		// TODO: implement reading in the LogFile
		break;
	default:
		throw std::exception("Invalid FileType provided on FileHandler::read");
	}

	// TODO: change to custom exceptions
}