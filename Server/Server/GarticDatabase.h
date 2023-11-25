#pragma once

#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

#include "Header Files/UsersEntity.h"
#include "Header Files/WordsEntity.h"
#include "BannedWordsEntity.h"
#include "QuotesEntity.h"
#include "HttpUtils.h"

using String = std::string;
using File = std::ifstream;
using UserVector = std::vector<http::UsersEntity>;
using WordEntityVector = std::vector<http::WordsEntity>;
using WordVector = std::vector<String>;

namespace http
{
	static inline auto CreateStorage(const String& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"UsersEntity",
				sql::make_column("id", &UsersEntity::SetId, &UsersEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("username", &UsersEntity::SetUsername, &UsersEntity::GetUsername),
				sql::make_column("password", &UsersEntity::SetPassword, &UsersEntity::GetPassword),
				sql::make_column("games_played", &UsersEntity::SetGamesPlayed, &UsersEntity::GetGamesPlayed),
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
			)
		);
	}

	using Storage = decltype(CreateStorage(""));

	class GarticStorage
	{
	public:
		bool Initialize();

		bool	   CheckCredentials(const String& givenUsername, const String& givenPassword);
		bool	   CheckUsernameAlreadyExists(const String& givenUsername);
		String	   FetchWord();
		UserVector FetchAllUsers();
		WordVector FetchAllWords();

		void	   CreateUser(const String& givenUsername, const String& givenPassword);
		void	   PopulateUsersEntity();
		void	   PopulateWordsEntity();
		void	   PopulateBannedWordsEntity();
		void	   PopulateQuotesEntity();

	private:
		int GenerateRandomId();

	private:
		const std::string kDbFile{ "products.sqlite" };
		const std::string kWordsFile{ "words.txt" };
		const std::string kUsersFile{ "users.txt" };
		const std::string kBannedWordsFile{ "banned words.txt" };
		const std::string kQuotesFile{ "quotes.txt" };

		Storage m_db = CreateStorage(kDbFile);
	};

	std::ostream& operator<<(std::ostream& out, const UserVector& users);
	std::ostream& operator<<(std::ostream& out, const WordVector& words);
}

