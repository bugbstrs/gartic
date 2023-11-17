#pragma once

#include "Database.h"

#include <fstream>

using WordEntityVector = std::vector<WordsEntity>;
using File = std::ifstream;
using WordVector = std::vector<std::string>;

class DatabaseManager
{
public:
	DatabaseManager() = delete;
	DatabaseManager(Storage& storage);

	void PopulateWordsEntity();
	void PopulateUsersEntity();

private:
	Storage& m_db;
};

