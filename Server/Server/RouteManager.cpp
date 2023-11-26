#include "RouteManager.h"
#include "CreateUserHandler.h"

void http::RouteManager::Run(GarticStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
	});

	CROW_ROUTE(m_app, "/fetchword")([&storage]() {
		std::vector<crow::json::wvalue> word_json;

		std::string fetchedWord = storage.FetchWord();

		word_json.push_back(crow::json::wvalue{ {"word", fetchedWord} });

		return crow::json::wvalue{ word_json };
	});

    CROW_ROUTE(m_app, "/fetchquote")([&storage]() {
        std::vector<crow::json::wvalue> quote_json;

        std::string fetchedQuote = storage.FetchQuote();

        quote_json.push_back(crow::json::wvalue{ {"quote", fetchedQuote} });

        return crow::json::wvalue{ quote_json };
    });

	auto& createUserPut = CROW_ROUTE(m_app, "/createuser")
		.methods(crow::HTTPMethod::PUT);
	createUserPut(CreateUserHandler(storage));

	CROW_ROUTE(m_app, "/fetchallwords")([&storage]() {
		std::vector<crow::json::wvalue> words_json;

		WordVector allWords = storage.FetchAllWords();

		for (const auto& word : allWords)
		{
			words_json.push_back( crow::json::wvalue{ {"word", word}});
		}

		return crow::json::wvalue{ words_json };
	});

	CROW_ROUTE(m_app, "/fetchallusers")([&storage]() {
		std::vector<crow::json::wvalue> users_json;

		UserVector allUsers = storage.FetchAllUsers();

		for (const auto& user : allUsers)
		{
			users_json.push_back(crow::json::wvalue{ 
				{ "username",     user.GetUsername()    }, 
				{ "points",       user.GetPoints()      },
				{ "games played", user.GetGamesPlayed() }
            });
		}

		return crow::json::wvalue{ users_json };
	});

    CROW_ROUTE(m_app, "/login")([&storage](const crow::request& request) {
        char* password = request.url_params.get("password");
        char* username = request.url_params.get("username");

        crow::response response;
        response.set_header("Content-Type", "application/json");
        
        if (password == nullptr || username == nullptr)
        {
            // todo: log
            response.code = 400;
            response.body = crow::json::wvalue({
                {"found", false}
            }).dump();

            return response;
        }

        bool foundCredentials = storage.CheckCredentials(String(username), String(password));
        
        response.code = foundCredentials ? 200 : 401;
        response.body = crow::json::wvalue({
            {"found", foundCredentials ? true : false}
        }).dump();

        return response;
    });

    CROW_ROUTE(m_app, "/register")([&storage](const crow::request& request) {
        char* password = request.url_params.get("password");
        char* username = request.url_params.get("username");

        crow::response response;
        response.set_header("Content-Type", "application/json");

        if (password == nullptr || username == nullptr) return crow::response(400);

        bool foundUser = storage.CheckUsernameAlreadyExists(String(username));

        if (foundUser) return crow::response(403);
        
        storage.CreateUser(String(username), String(password));
        return crow::response(201);
    });

    CROW_ROUTE(m_app, "/bannedword")([&storage](const crow::request& request) {
        char* word = request.url_params.get("name");

        if (word == nullptr) return crow::response(400);

        bool checkBannedWord = storage.CheckBannedWord(String(word));

        return checkBannedWord ? crow::response(201) : crow::response(403);
    });

	m_app
        .port(18080)
        .multithreaded()
        .run();
}
