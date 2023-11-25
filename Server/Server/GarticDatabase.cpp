#include "GarticDatabase.h"

#include "print"

#include <random>

using namespace http;

bool http::GarticStorage::Initialize()
{
	m_db.sync_schema();
	auto initWordsCount = m_db.count<WordsEntity>();
	if (!initWordsCount)
	{
		PopulateWordsEntity();
	}
	auto wordsCount = m_db.count<WordsEntity>();

	auto initUsersCount = m_db.count<UsersEntity>();
	if (!initUsersCount)
	{
		PopulateUsersEntity();
	}
	auto usersCount = m_db.count<UsersEntity>();

	auto initBannedWordsCount = m_db.count<BannedWordsEntity>();
	if (!initBannedWordsCount)
	{
		PopulateBannedWordsEntity();
	}
	auto bannedWordsCount = m_db.count<BannedWordsEntity>();


	return wordsCount != 0 && usersCount != 0 && bannedWordsCount != 0;
}

bool GarticStorage::CheckCredentials(const String& givenUsername, const String& givenPassword) 
{
	auto result1 = m_db.select(sql::columns(&UsersEntity::GetId, &UsersEntity::GetUsername),
		sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetUsername, givenUsername)));

	auto result2 = m_db.select(sql::columns(&UsersEntity::GetId, &UsersEntity::GetUsername), sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetPassword, givenPassword)));

	return !result1.empty() && !result2.empty();
}

bool GarticStorage::CheckUsernameAlreadyExists(const String& givenUsername)
{
	auto result = m_db.select(sqlite_orm::columns(&UsersEntity::GetId, &UsersEntity::GetUsername),
		sqlite_orm::where(sqlite_orm::is_equal(&UsersEntity::GetUsername, givenUsername)));

	return !result.empty();
}

String GarticStorage::FetchWord()
{
	int randomId = GenerateRandomId();

	auto result = m_db.select(sqlite_orm::columns(&WordsEntity::GetName),
		sqlite_orm::where(sqlite_orm::is_equal(&WordsEntity::GetId, randomId)));

	if (!result.empty())
	{
		return std::get<0>(result[0]);
	}
}

UserVector GarticStorage::FetchAllUsers()
{
	UserVector allUsers;

	auto users = m_db.get_all<UsersEntity>();
	for (const auto& user : users)
	{
		allUsers.push_back(user);
	}

	return allUsers;
}

WordVector GarticStorage::FetchAllWords()
{
	WordVector allWords;

	auto words = m_db.get_all<WordsEntity>();
	for (const auto& word : words)
	{
		allWords.push_back(word.GetName());
	}

	return allWords;
}

void GarticStorage::CreateUser(int gamesPlayed, int points, const String& givenUsername, const String& givenPassword)
{
	if (CheckUsernameAlreadyExists(givenUsername))
	{
		return;		// possible exception to throw here
	}

	m_db.insert(UsersEntity{ gamesPlayed, points, givenUsername, givenPassword });
}

void GarticStorage::PopulateUsersEntity()
{
	int						 points;
	int						 gamesPlayed;
	std::ifstream			 filename;
	std::string				 password;
	std::string				 username;
	std::vector<UsersEntity> users;

	filename.open(kUsersFile);

	while (filename >> gamesPlayed >> points >> username >> password)
	{
		users.push_back(UsersEntity{ gamesPlayed, points, username, password });
	}

	for (const auto& user : users)
	{
		m_db.insert(user);
	}

	filename.close();
}

void GarticStorage::PopulateWordsEntity()
{
	std::ifstream filename;
	std::string   word;
	WordVector    words;

	filename.open(kWordsFile);

	while (filename >> word)
	{
		words.push_back(word);
	}

	for (const auto& word : words)
	{
		m_db.insert(WordsEntity{ word });
	}

	filename.close();
}

void http::GarticStorage::PopulateBannedWordsEntity()
{
	std::ifstream filename;
	std::string bannedWord;
	WordVector bannedWords;

	filename.open(kBannedWordsFile);

	while (filename >> bannedWord)
	{
		bannedWords.push_back(bannedWord);
	}

	for (const auto& bannedWord : bannedWords)
	{
		m_db.insert(BannedWordsEntity{ bannedWord });
	}

	filename.close();
}


int GarticStorage::GenerateRandomId()
{
	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	auto							   count = m_db.count<WordsEntity>();
	std::uniform_int_distribution<int> distribution(0, count - 1);

	return distribution(engine);
}

// External operators

std::ostream& http::operator<<(std::ostream& out, const UserVector& users)
{
	std::print(out, "Users: ");

	for (const auto& user : users)
	{
		std::print(
			out,
			"id: {} username: {} password: {} points: {} games played: {} \n",
			user.GetId(),
			user.GetUsername(),
			user.GetPassword(),
			user.GetPoints(),
			user.GetGamesPlayed()
		);
	}


	return out;
}

std::ostream& http::operator<<(std::ostream& out, const WordVector& words)
{
	std::print(out, "Words: ");

	for (const auto& word : words)
	{
		std::print(out, "name: {}\n", word);
	}

	return out;
}
