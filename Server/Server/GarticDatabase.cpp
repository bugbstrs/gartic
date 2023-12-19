#include "GarticDatabase.h"

import GarticExceptions;

#include "print"

#include <random>

using namespace http;
using namespace sqlite_orm;

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

	auto initQuotesCount = m_db.count<QuotesEntity>();
	if (!initQuotesCount)
	{
		PopulateQuotesEntity();
	}
	auto quotesCount = m_db.count<QuotesEntity>();


	return wordsCount != 0 && usersCount != 0 && bannedWordsCount != 0 && quotesCount != 0;
}

bool GarticStorage::CheckCredentials(const String& givenUsername, const String& givenPassword) 
{
    auto users = m_db.get_all<UsersEntity>(
        where(
            c(&UsersEntity::GetUsername) == givenUsername &&
            c(&UsersEntity::GetPassword) == givenPassword
        )
    );

    return !users.empty();
}

bool GarticStorage::CheckUsernameAlreadyExists(const String& givenUsername)
{
	auto result = m_db.get_all<UsersEntity>(
		where(
			c(&UsersEntity::GetUsername) == givenUsername
		)
	);

	return !result.empty();
}

bool http::GarticStorage::CheckBannedWord(const String& givenWord)
{
	auto result = m_db.get_all<BannedWordsEntity>(
		where(
			c(&BannedWordsEntity::GetName) == givenWord
		)
	);

	return !result.empty();
}

String GarticStorage::FetchWord()
{
	int randomId = GenerateRandomId(true);

	auto result = m_db.select(sqlite_orm::columns(&WordsEntity::GetName),
		where(
			c(&WordsEntity::GetId) == randomId
		)
	);

	if (!result.empty())
	{
		return std::get<0>(result[0]);
	}

	/*throw GarticException<CannotFetchWordException>("GarticStroage > FetchWord(): Word could not be fetched!");*/
}

String http::GarticStorage::FetchQuote()
{
	int randomId = GenerateRandomId(false);

	auto result = m_db.select(sqlite_orm::columns(&QuotesEntity::GetName),
		where(
			c(&QuotesEntity::GetId) == randomId
		)
	);

	if (!result.empty())
	{
		return std::get<0>(result[0]);
	}
	
	/*throw GarticException<CannotFetchQuoteException>("GarticStorage > FetchQuote(): Quote could not be fetched!");*/
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

UserVector http::GarticStorage::FetchTop5Users()
{
	UserVector allUsers = FetchAllUsers();

	std::sort(allUsers.begin(), allUsers.end(), [](const UsersEntity& user1, const UsersEntity& user2) {
		return user1.GetPoints() < user2.GetPoints();
	});

	int numTopUsers = std::min(5, static_cast<int>(allUsers.size()));

	return UserVector(allUsers.begin(), allUsers.begin() + numTopUsers);
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

void GarticStorage::CreateUser(const String& givenUsername, const String& givenPassword)
{
	if (CheckUsernameAlreadyExists(givenUsername))
	{
		//throw GarticException<UserAlreadyExistsException>("GarticStorage > CreateUser(): User already exists!");
	}

	m_db.insert(UsersEntity{ 0, 0, givenUsername, givenPassword });
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

void http::GarticStorage::PopulateQuotesEntity()
{
	std::ifstream filename;
	std::string	  quote;
	WordVector    quotes;

	filename.open(kQuotesFile);

	while (filename >> quote)
	{
		quotes.push_back(quote);
	}

	for (const auto& quote : quotes)
	{
		m_db.insert(QuotesEntity{ quote });
	}

	filename.close();
}

int GarticStorage::GenerateRandomId(bool isWordsEntity)
{
	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	auto							   count = isWordsEntity ? m_db.count<WordsEntity>() : m_db.count<QuotesEntity>();
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
