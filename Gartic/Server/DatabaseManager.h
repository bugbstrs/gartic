#pragma once

#include "Database.h"

#include <fstream>
#include <tuple>

using WordEntityVector = std::vector<WordsEntity>;
using File = std::ifstream;
using WordVector = std::vector<std::string>;
using UserVector = std::vector<UsersEntity>;

class DatabaseManager
{
public:
	DatabaseManager() = delete;
	DatabaseManager(Storage& storage);

	void PopulateWordsEntity();
	void PopulateUsersEntity();

	WordVector FetchAllWords();
	UserVector FetchAllUsers();

private:
	Storage& m_db;
};

std::ostream& operator<<(std::ostream& out, const WordVector& words);

std::ostream& operator<<(std::ostream& out, const UserVector& users);
