#include <filesystem>
#include <iostream>
#include <memory>
#include <crow.h>

#include "DatabaseManager.h"

int main()
{
	const std::string db_file = "gartic.sqlite";
	Storage db = Database::createStorage(db_file);
	db.sync_schema();

	DatabaseManager manager{ db };
	
	manager.PopulateWordsEntity();
	manager.PopulateUsersEntity();

	WordVector words{manager.FetchAllWords()};
	UserVector users{manager.FetchAllUsers()};

	std::cout << words << std::endl;
	std::cout << users << std::endl;

	return 0;
}