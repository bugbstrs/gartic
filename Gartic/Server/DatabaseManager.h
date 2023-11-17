#pragma once

#include "Database.h"

#include <fstream>
#include <tuple>
#include <random>

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

	bool CheckCredentials(const String& givenUsername, const String& givenPassword) const;
	bool CheckUsernameAlreadyExists(const String& givenUsername) const;

	void CreateUser(const String& givenUsername, const String& givenPassword) const;

	String FetchWord();

private:
	Storage& m_db;

	int GenerateRandomId() const;
};

std::ostream& operator<<(std::ostream& out, const WordVector& words);

std::ostream& operator<<(std::ostream& out, const UserVector& users);
