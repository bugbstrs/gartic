#include "RouteManager.h"

void http::RouteManager::Run(GarticStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
	});

	CROW_ROUTE(m_app, "/FetchWord")([&storage]() {
		std::vector<crow::json::wvalue> words_json;

		std::string fetchedWord = storage.FetchWord();

		words_json.push_back(crow::json::wvalue{ {"word", fetchedWord} });

		return crow::json::wvalue{ words_json };
		});

	m_app.port(18080).multithreaded().run();
}
