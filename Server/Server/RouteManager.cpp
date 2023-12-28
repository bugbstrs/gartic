#include "RouteManager.h"

#include <sstream>
#include <regex>

import GarticExceptions;

http::RouteManager::RouteManager(GarticStorage& storage, GarticManager& manager) :
	m_storage{ storage },
	m_gartic{ manager }
{}

void http::RouteManager::Run()
{
	CROW_ROUTE(m_app, "/")([]() {
		return "This is an example app of crow and sql-orm";
		});

	FetchWordRoute();
	FetchQuoteRoute();
	FetchAllWordsRoute();
	FetchAllUsersRoute();
	FetchTop5UsersRoute();
	LoginRoute();
	RegisterRoute();
	CheckBannedWordRoute();
	PutWordToGuessRoute();
	GetWordToDisplayRoute();

	m_app
		.port(18080)
		.multithreaded()
		.run();
}

void http::RouteManager::FetchWordRoute()
{
	CROW_ROUTE(m_app, "/fetchword")([this]() {
		std::vector<crow::json::wvalue> word_json;

		std::string fetchedWord;

		try
		{
			fetchedWord = m_storage.FetchWord();
			word_json.push_back(crow::json::wvalue{ {"word", fetchedWord} });
		}
		catch (CannotFetchWordException& exception)
		{
			word_json.push_back(crow::json::wvalue{ {"word", "N/A"} });
		}

		return crow::json::wvalue{ word_json };
		});
}

void http::RouteManager::FetchQuoteRoute()
{
	CROW_ROUTE(m_app, "/fetchquote")([this]() {
		std::vector<crow::json::wvalue> quote_json;

		std::string fetchedQuote;

		try
		{
			fetchedQuote = m_storage.FetchQuote();
			quote_json.push_back(crow::json::wvalue{ {"quote", fetchedQuote} });
		}
		catch (CannotFetchQuoteException& exception)
		{
			quote_json.push_back(crow::json::wvalue{ {"quote", "N/A"} });
		};

		return crow::json::wvalue{ quote_json };
		});
}

void http::RouteManager::FetchAllWordsRoute()
{
	CROW_ROUTE(m_app, "/fetchallwords")([this]() {
		std::vector<crow::json::wvalue> words_json;

		WordVector allWords = m_storage.FetchAllWords();

		for (const auto& word : allWords)
		{
			words_json.push_back(crow::json::wvalue{ {"word", word} });
		}

		return crow::json::wvalue{ words_json };
		});
}

void http::RouteManager::FetchAllUsersRoute()
{
	CROW_ROUTE(m_app, "/fetchallusers")([this]() {
		std::vector<crow::json::wvalue> users_json;

		UserVector allUsers = m_storage.FetchAllUsers();

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

void http::RouteManager::FetchTop5UsersRoute()
{
	CROW_ROUTE(m_app, "/fetchtopusers")([this]() {
		std::vector<crow::json::wvalue> top_users_json;

		UserVector topUsers = m_storage.FetchTop5Users();

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

void http::RouteManager::LoginRoute()
{
	CROW_ROUTE(m_app, "/login")([this](const crow::request& request) {
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

		bool foundCredentials = m_storage.CheckCredentials(String(username), String(password));

		response.code = foundCredentials ? 200 : 401;
		response.body = crow::json::wvalue({
			{"found", foundCredentials ? true : false}
			}).dump();

			return response;
		});
}

void http::RouteManager::RegisterRoute()
{
	CROW_ROUTE(m_app, "/register")([this](const crow::request& request) {
		char* password = request.url_params.get("password");
		char* username = request.url_params.get("username");

		crow::response response;
		response.set_header("Content-Type", "application/json");

		if (password == nullptr || username == nullptr) return crow::response(400);

		try
		{
			m_storage.CreateUser(String(username), String(password));
		}
		catch (UserAlreadyExistsException& exception)
		{
			return crow::response(403);
		}

		return crow::response(201);
		});
}

void http::RouteManager::CheckBannedWordRoute()
{
	CROW_ROUTE(m_app, "/bannedword")([this](const crow::request& request) {
		char* word = request.url_params.get("name");

		if (word == nullptr) return crow::response(400);

		bool checkBannedWord = m_storage.CheckBannedWord(String(word));

		return checkBannedWord ? crow::response(201) : crow::response(403);
		});
}

std::optional<crow::response> http::RouteManager::IsRequestAuthenticatedRoute(const crow::request& request)
{
	std::optional<crow::response> returnResponse;
	char* password = request.url_params.get("password");
	char* username = request.url_params.get("username");
	crow::response response;
	std::regex regexFormatSHA256{ "[a-f0-9]{64}" };
	std::regex regexFormatUsername{ "^[a-z]+[a-z0-9_-]*[a-z]+$" };

	if (password == nullptr || username == nullptr)
	{
		response.code = 400;
		response.set_header("Content-Type", "application/json");
		response.body = crow::json::wvalue
		({
			{"code", response.code},
			{"error", "user or password not provided"}
			}).dump();

			return response;
	}

	// length of SHA256 hash when converted to hex string
	if (std::strlen(password) != 64 || !std::regex_match(password, regexFormatSHA256))
	{
		response.code = 400;
		response.body = crow::json::wvalue
		({
			{"code", response.code},
			{"error", "invalid password format! (not hashed or bad hash)"}
			}).dump();

			return response;
	}

	if (!std::regex_match(username, regexFormatUsername))
	{
		response.code = 400;
		response.body = crow::json::wvalue
		({
			{"code", response.code},
			{"error", "invalid username format! ((username format description))"}
			}).dump();

			return response;
	}

	bool foundCredentials = m_storage.CheckCredentials(String(username), String(password));

	if (!foundCredentials)
	{
		response.code = 401;
		response.body = crow::json::wvalue
		({
			{"code", response.code},
			{"error", "unauthorized"}
			}).dump();
	}

	return {};
}

void http::RouteManager::CreateLobbyRoute()
{
	CROW_ROUTE(m_app, "/createlobby")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		crow::response response;

		if (username == nullptr)
		{
			// todo: log
			response.code = 400;
			response.body = crow::json::wvalue({
				{"found", false}
				}).dump();

				return response;
		}

		std::string usernameString(username);
		std::string passwordString(password);

		if (!m_storage.CheckCredentials(usernameString, passwordString))
		{
			// todo: log
			response.code = 401;
			response.body = crow::json::wvalue({
				{"no_user", false}
				}).dump();

				return response;
		}

		m_gartic.CreateLobby(usernameString);

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}

void http::RouteManager::CreateGameRoute()
{
	CROW_ROUTE(m_app, "/creategame")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		crow::response response;

		if (username == nullptr)
		{
			// todo: log
			response.code = 400;
			response.body = crow::json::wvalue({
				{"found", false}
				}).dump();

				return response;
		}

		std::string usernameString(username);
		std::string passwordString(password);

		if (!m_storage.CheckCredentials(usernameString, passwordString))
		{
			// todo: log
			response.code = 401;
			response.body = crow::json::wvalue({
				{"no_user", false}
				}).dump();

				return response;
		}

		m_gartic.CreateGame(std::string(username));

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}

void http::RouteManager::FetchCodeRoute()
{
	CROW_ROUTE(m_app, "/fetchcode")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<crow::json::wvalue> code_json;

		std::string fetchedCode;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedCode = m_gartic.GetLobby(std::string(username))->GetCode();
			code_json.push_back(crow::json::wvalue{ {"code", fetchedCode} });
		}
		else
		{
			code_json.push_back(crow::json::wvalue{ {"code", "N/A"} });
		}

		return crow::json::wvalue{ code_json };
		});
}

void http::RouteManager::FetchUsersRoute()
{
	CROW_ROUTE(m_app, "/fetchusers")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<std::shared_ptr<User>> fetchedUsers;
		
		std::vector<crow::json::wvalue> users_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedUsers = m_gartic.GetLobby(std::string(username))->GetUsers();
			for (const auto& user : fetchedUsers)
			{
				users_json.push_back(crow::json::wvalue{ {"username", user->GetUsername()} });
			}
		}
		else
		{
			users_json.push_back(crow::json::wvalue{ {"username", "N/A"} });
		}

		return crow::json::wvalue{ users_json };
		});
}

void http::RouteManager::FetchSettingsRoute()
{
	CROW_ROUTE(m_app, "/fetchsettings")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		
		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<crow::json::wvalue> settings_json;
		
		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			GameSettings fetchedSettings{ m_gartic.GetLobby(std::string(username))->GetSettings() };
			settings_json.push_back(crow::json::wvalue{ {"roundsNumber", fetchedSettings.GetRoundsNumber()}});
			settings_json.push_back(crow::json::wvalue{ {"playersNumber", fetchedSettings.GetPlayersNumber()}});
			settings_json.push_back(crow::json::wvalue{ {"drawTime", fetchedSettings.GetDrawTime()}});
			settings_json.push_back(crow::json::wvalue{ {"isCustomRound", fetchedSettings.GetCustomRounds()}});
		}
		else
		{
			settings_json.push_back(crow::json::wvalue{ {"roundsNumber", "N/A"} });
			settings_json.push_back(crow::json::wvalue{ {"playersNumber", "N/A"} });
			settings_json.push_back(crow::json::wvalue{ {"drawTime", "N/A"} });
			settings_json.push_back(crow::json::wvalue{ {"isCustomRound", "N/A"} });
		}

		return crow::json::wvalue{ settings_json };
		});
}

void http::RouteManager::FetchPlayersRoute()
{
	CROW_ROUTE(m_app, "/fetchplayers")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<Player*> fetchedPlayers;

		std::vector<crow::json::wvalue> players_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedPlayers = m_gartic.GetGame(usernameString)->GetPlayers();
			for (const auto& player : fetchedPlayers)
			{
				players_json.push_back(crow::json::wvalue{ {"username", player->GetName()} });
			}
		}
		else
		{
			players_json.push_back(crow::json::wvalue{ {"username", "N/A"} });
		}

		return crow::json::wvalue{ players_json };
		});
}

void http::RouteManager::FetchGameStatusRoute()
{
	CROW_ROUTE(m_app, "/fetchplayers")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		GameStatus fetchedStatus;

		std::vector<crow::json::wvalue> status_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedStatus = m_gartic.GetGame(usernameString)->GetStatus();

			std::string statusString = GameStatusWrapper::ToString(fetchedStatus);

			status_json.push_back(crow::json::wvalue{ {"game_status", statusString} });
		}
		else
		{
			status_json.push_back(crow::json::wvalue{ {"game_status", "N/A"} });
		}

		return crow::json::wvalue{ status_json };
		});
}

void http::RouteManager::FetchRoundNumberRoute()
{
	CROW_ROUTE(m_app, "/fetchroundnumber")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		int fetchedNumber;

		std::vector<crow::json::wvalue> roundNumber_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedNumber = m_gartic.GetGame(usernameString)->GetRoundNumber();

			roundNumber_json.push_back(crow::json::wvalue{ {"round_number", std::to_string(fetchedNumber)}});
		}
		else
		{
			roundNumber_json.push_back(crow::json::wvalue{ {"round_number", "N/A"} });
		}

		return crow::json::wvalue{ roundNumber_json };
		});
}

void http::RouteManager::FetchDrawerRoute()
{
	CROW_ROUTE(m_app, "/fetchdrawer")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		Player* fetchedDrawer;

		std::vector<crow::json::wvalue> drawer_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedDrawer = m_gartic.GetGame(usernameString)->GetRound().GetDrawer();

			drawer_json.push_back(crow::json::wvalue{ {"drawer", fetchedDrawer->GetName()}});
		}
		else
		{
			drawer_json.push_back(crow::json::wvalue{ {"drawer", "N/A"} });
		}

		return crow::json::wvalue{ drawer_json };
		});
}

void http::RouteManager::PutWordToGuessRoute()
{
	CROW_ROUTE(m_app, "/putwordtoguess")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		char* wordToDisplay = request.url_params.get("word");
		
		std::string usernameString(username);
		std::string passwordString(password);

		crow::response response;

		if (wordToDisplay == nullptr)
		{
			// todo: log
			response.code = 400;
			response.body = crow::json::wvalue({
				{"found", false}
				}).dump();

				return response;
		}
		
		if (!m_storage.CheckCredentials(usernameString, passwordString))
		{
			// todo: log
			response.code = 401;
			response.body = crow::json::wvalue({
				{"no_user", false}
				}).dump();

				return response;
		}

		std::string wordToDiplayString(wordToDisplay);
		m_gartic.GetGame(usernameString)->GetRound().SetWordToDisplay(wordToDiplayString);

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}

void http::RouteManager::GetWordToDisplayRoute()
{
	CROW_ROUTE(m_app, "/fetchwordtodisplay")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		
		std::vector<crow::json::wvalue> word_json;

		std::string usernameString(username);
		std::string passwordString(password);

		std::string wordToDisplay;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			wordToDisplay = m_gartic.GetGame(usernameString)->GetRound().GetWordToDisplay();

			word_json.push_back(crow::json::wvalue{ {"word", wordToDisplay} });
		}
		else
		{
			word_json.push_back(crow::json::wvalue{ {"word", "N/A"} });
		}

		return crow::json::wvalue{ word_json };
		});
}