#include "RouteManager.h"
#include "CreateUserHandler.h"

void http::RouteManager::Run(GarticStorage& storage)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
	});

	m_app
        .port(18080)
        .multithreaded()
        .run();
}

void http::RouteManager::CreateFetchWordRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/fetchword")([&storage]() {
        std::vector<crow::json::wvalue> word_json;

        std::string fetchedWord;
        
        try
        {
            fetchedWord = storage.FetchWord();
            word_json.push_back(crow::json::wvalue{ {"word", fetchedWord} });
        }
        catch (CannotFetchWordException& exception)
        {
            word_json.push_back(crow::json::wvalue{ {"word", "N/A"}});
        }

        return crow::json::wvalue{ word_json };
    });
}

void http::RouteManager::CreateFetchQuoteRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/fetchquote")([&storage]() {
        std::vector<crow::json::wvalue> quote_json;

        std::string fetchedQuote;

        try
        {
            fetchedQuote = storage.FetchQuote();
            quote_json.push_back(crow::json::wvalue{ {"quote", fetchedQuote} });
        }
        catch (CannotFetchQuoteException& exception)
        {
            quote_json.push_back(crow::json::wvalue{ {"quote", "N/A"} });
        };

        return crow::json::wvalue{ quote_json };
    });
}

void http::RouteManager::CreateFetchAllWordsRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/fetchallwords")([&storage]() {
        std::vector<crow::json::wvalue> words_json;

        WordVector allWords = storage.FetchAllWords();

        for (const auto& word : allWords)
        {
            words_json.push_back(crow::json::wvalue{ {"word", word} });
        }

        return crow::json::wvalue{ words_json };
    });
}

void http::RouteManager::CreateFetchAllUsersRoute(GarticStorage& storage)
{
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
}

void http::RouteManager::CreateFetchTop5UsersRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/fetchtopusers")([&storage]() {
        std::vector<crow::json::wvalue> top_users_json;

        UserVector topUsers = storage.FetchTop5Users();

        for (const auto& user : topUsers)
        {
            top_users_json.push_back(crow::json::wvalue{
                { "username",     user.GetUsername()    },
                { "points",       user.GetPoints()      },
                { "games played", user.GetGamesPlayed() }
                });
        }

        return crow::json::wvalue{ top_users_json };
    });
}

void http::RouteManager::CreateLoginRoute(GarticStorage& storage)
{
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
}

void http::RouteManager::CreateRegisterRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/register")([&storage](const crow::request& request) {
        char* password = request.url_params.get("password");
        char* username = request.url_params.get("username");

        crow::response response;
        response.set_header("Content-Type", "application/json");

        if (password == nullptr || username == nullptr) return crow::response(400);

        try
        {
            storage.CreateUser(String(username), String(password));
        }
        catch (UserAlreadyExistsException& exception)
        {
            return crow::response(403);
        }

        return crow::response(201);
    });
}

void http::RouteManager::CreateCheckBannedWordRoute(GarticStorage& storage)
{
    CROW_ROUTE(m_app, "/bannedword")([&storage](const crow::request& request) {
        char* word = request.url_params.get("name");

        if (word == nullptr) return crow::response(400);

        bool checkBannedWord = storage.CheckBannedWord(String(word));

        return checkBannedWord ? crow::response(201) : crow::response(403);
    });
}
