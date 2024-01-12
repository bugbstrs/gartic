#include "GarticDatabase.h"

import GarticExceptions;

#include "print"

#include <random>

using namespace http;
using namespace sqlite_orm;

bool http::GarticStorage::Initialize()
{
	m_db.sync_schema();
	auto initGameHisCount = m_db.count<GameHistoryEntity>();
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
	auto result = m_db.select(sqlite_orm::columns(&BannedWordsEntity::GetId),
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

	throw GarticException<CannotFetchWordException>("GarticStorage > FetchWord(): Word could not be fetched!");
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

	throw GarticException<CannotFetchQuoteException>("GarticStorage > FetchQuote(): Quote could not be fetched!");
}

std::vector<std::pair<int, int>> http::GarticStorage::FetchAllHistoriesOf(const String& givenUsername)
{
	auto result = 
	m_db.select(
		sql::columns(&GameHistoryEntity::GetId, &GameHistoryEntity::GetPosition, &GameHistoryEntity::GetTotalPoints),
		sql::inner_join<UsersEntity>(sql::on(sql::c(&UsersEntity::GetId) == &GameHistoryEntity::GetUserId))
	);
	
	std::vector<std::pair<int, int>> statsForProfile;

	for (int index = 0; index < result.size(); index++)
	{
		statsForProfile.push_back(std::make_pair(std::get<1>(result[index]), std::get<2>(result[index])));
	}

	return statsForProfile;
}

void GarticStorage::CreateUser(const String& givenUsername, const String& givenPassword)
{
	if (CheckUsernameAlreadyExists(givenUsername))
	{
		throw GarticException<UserAlreadyExistsException>("GarticStorage > CreateUser(): User already exists!");
	}

	m_db.insert(UsersEntity{ 0, givenUsername, givenPassword });
}

void GarticStorage::PopulateUsersEntity()
{
	int						 points;
	std::ifstream			 filename;
	std::string				 password;
	std::string				 username;
	std::vector<UsersEntity> users;

	filename.open(kUsersFile);

	while (filename >> points >> username >> password)
	{
		users.push_back(UsersEntity{ points, username, password });
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

void http::GarticStorage::PopulateGameHistoryEntity(const std::vector<std::shared_ptr<Player>>& leaderboard)
{
	for (int index = 0; index < leaderboard.size(); index++)
	{
		auto currentUser = m_db.select(columns(&UsersEntity::GetId), where(c(&UsersEntity::GetUsername) == leaderboard[index]->GetName()));

		if (!currentUser.empty())
		{
			auto id = std::get<0>(currentUser[0]);

			m_db.insert(GameHistoryEntity{ id, index + 1, leaderboard[index]->GetPoints() });
		}
	}
}

int GarticStorage::GenerateRandomId(bool isWordsEntity)
{
	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	auto							   count = isWordsEntity ? m_db.count<WordsEntity>() : m_db.count<QuotesEntity>();
	std::uniform_int_distribution<int> distribution(1, count);

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
			"id: {} username: {} password: {} points: {}\n",
			user.GetId(),
			user.GetUsername(),
			user.GetPassword(),
			user.GetPoints()
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
