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

	auto words = db.get_all<WordsEntity>();
	for (const auto& word : words) {
		std::cout << "Word Name: " << word.GetName() << std::endl;
	}

	//if (initProductsCount == 0)
	//	populateStorage(db);

	//auto productsCount = db.count<WordsEntity>();
	//std::cout << "productsCount = " << productsCount << '\n';
	return 0;
}