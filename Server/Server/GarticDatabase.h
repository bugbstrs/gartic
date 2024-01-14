#pragma once

#include <string>
#include <vector>
#include <memory>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

#include "UsersEntity.h"
#include "WordsEntity.h"
#include "BannedWordsEntity.h"
#include "QuotesEntity.h"
#include "GameHistoryEntity.h"
#include "HttpUtils.h"

#include "Player.h"

// Exceptions

//import "UserAlreadyExistsException.h";
//import "CannotFetchWordException.h";
//import "CannotFetchQuoteException.h";

using File = std::ifstream;
using UserVector = std::vector<http::UsersEntity>;
using WordEntityVector = std::vector<http::WordsEntity>;
using WordVector = std::vector<std::string>;

namespace http
{
	static inline auto CreateStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"UsersEntity",
				sql::make_column("id", &UsersEntity::SetId, &UsersEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("username", &UsersEntity::SetUsername, &UsersEntity::GetUsername),
				sql::make_column("password", &UsersEntity::SetPassword, &UsersEntity::GetPassword),
				sql::make_column("points", &UsersEntity::SetPoints, &UsersEntity::GetPoints)
			),
			sql::make_table(
				"WordsEntity",
				sql::make_column("id", &WordsEntity::SetId, &WordsEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("name", &WordsEntity::SetName, &WordsEntity::GetName)
			),
			sql::make_table(
				"BannedWordsEntity",
				sql::make_column("id", &BannedWordsEntity::SetId, &BannedWordsEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("name", &BannedWordsEntity::SetName, &BannedWordsEntity::GetName)
			),
			sql::make_table(
				"QuotesEntity",
				sql::make_column("id", &QuotesEntity::SetId, &QuotesEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("name", &QuotesEntity::SetName, &QuotesEntity::GetName)
			),
			sql::make_table(
				"GameHistoryEntity",
				sql::make_column("id", &GameHistoryEntity::SetId, &GameHistoryEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("userId", &GameHistoryEntity::SetUserId, &GameHistoryEntity::GetUserId),
				sql::make_column("position", &GameHistoryEntity::SetPosition, &GameHistoryEntity::GetPosition),
				sql::make_column("totalPoints", &GameHistoryEntity::SetTotalPoints, &GameHistoryEntity::GetTotalPoints)
			)
		);
	}

	using Storage = decltype(CreateStorage(""));

	class GarticStorage
	{
	public:
		bool Initialize();

		bool	   CheckCredentials(const std::string& givenUsername, const std::string& givenPassword);
		bool	   CheckUsernameAlreadyExists(const std::string& givenUsername);
		bool	   CheckBannedWord(const std::string& givenWord);

		std::string	   FetchWord();
		std::string	   FetchQuote();
		
		std::vector<std::pair<int, int>> FetchAllHistoriesOf(const std::string& givenUsername);

		void	   CreateUser(const std::string& givenUsername, const std::string& givenPassword);
		void	   PopulateUsersEntity();
		void	   PopulateWordsEntity();
		void	   PopulateBannedWordsEntity();
		void	   PopulateQuotesEntity();
		void	   PopulateGameHistoryEntity(const std::vector<std::shared_ptr<Player>>& leaderboard);

	private:
		int GenerateRandomId(bool isWordsEntity);

	private:
		const std::string kDbFile{ "Gartic.sqlite" };
		const std::string kWordsFile{ "words.txt" };
		const std::string kUsersFile{ "users.txt" };
		const std::string kBannedWordsFile{ "banned.txt" };
		const std::string kQuotesFile{ "quotes.txt" };

		Storage m_db = CreateStorage(kDbFile);
	};

	std::ostream& operator<<(std::ostream& out, const UserVector& users);
	std::ostream& operator<<(std::ostream& out, const WordVector& words);
}

