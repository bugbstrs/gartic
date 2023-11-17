export module Database;

import <string>;
import UsersEntity;
import WordsEntity;

#include <sqlite_orm/sqlite_orm.h>

namespace sql = sqlite_orm;

using String = std::string;

export class Database
{
public:
	static inline auto createStorage(const std::string& filename)
	{
		return sql::make_storage(
			filename,
			sql::make_table(
				"Users",
				sql::make_column("id", &UsersEntity::SetId, &UsersEntity::GetId, sql::primary_key().autoincrement()),
				sql::make_column("username", &UsersEntity::SetUsername, &UsersEntity::GetUsername),
				sql::make_column("password", &UsersEntity::SetPassword, &UsersEntity::GetPassword),
				sql::make_column("games_played", &UsersEntity::SetGamesPlayed, &UsersEntity::GetGamesPlayed),
				sql::make_column("points", &UsersEntity::SetPoints, &UsersEntity::GetPoints),
				sql::make_column("previous_scores", &UsersEntity::SetPrevScores, &UsersEntity::GetPrevScores)
			),
			sql::make_table(
				"Words",
				sql::make_column("name", &WordsEntity::SetName, & WordsEntity::GetName, sql::primary_key().autoincrement())
			)
		);
	}
};

using Storage = decltype(Database::createStorage(""));

export void populateStorage(Storage& storage)
{
	std::vector<WordsEntity> words{
	WordsEntity{"Milk"},
	WordsEntity{"Egg"},
	WordsEntity{"Flour"},
	WordsEntity{"Butter"},
	WordsEntity{"Salt"},
	WordsEntity{"Jam"}
	};
	storage.insert_range(words.begin(), words.end());
}
