#pragma once
#include "UsersEntity.h"
#include "WordsEntity.h"

#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

class Database
{
public:
	Database() = delete;

	static inline auto createStorage(const std::string& filename)
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
			)
		);
	}
};

using Storage = decltype(Database::createStorage(""));