#pragma once

#include "Database.h"

#include <fstream>
#include <tuple>
#include <random>

using File             = std::ifstream;
using UserVector       = std::vector<UsersEntity>;
using WordEntityVector = std::vector<WordsEntity>;
using WordVector       = std::vector<std::string>;

class DatabaseManager
{
public:
	DatabaseManager() = delete;
	DatabaseManager(Storage& storage);

	bool	   CheckCredentials(const String& givenUsername, const String& givenPassword) const;
	bool	   CheckUsernameAlreadyExists(const String& givenUsername)					  const;
	String	   FetchWord();
	UserVector FetchAllUsers();
	void	   CreateUser(const String& givenUsername, const String& givenPassword)		  const;
	void	   PopulateUsersEntity();
	void	   PopulateWordsEntity();
	WordVector FetchAllWords();

private:
	Storage& m_db;

	int GenerateRandomId() const;
};

std::ostream& operator<<(std::ostream& out, const UserVector& users);
std::ostream& operator<<(std::ostream& out, const WordVector& words);