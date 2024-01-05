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
	FetchWordRoute();
	FetchQuoteRoute();
	FetchAllWordsRoute();
	FetchAllUsersRoute();
	FetchTop5UsersRoute();
	LoginRoute();
	RegisterRoute();
	CheckBannedWordRoute();
	CreateLobbyRoute();
	CreateGameRoute();
	JoinLobbyRoute();
	FetchCodeRoute();
	FetchUsersRoute();
	FetchSettingsRoute();
	FetchLobbyStatusRoute();
	LeaveLobbyRoute();
	FetchPlayersRoute();
	FetchGameStatusRoute();
	FetchRoundNumberRoute();
	FetchDrawerRoute();
	FetchNWordsRoute();
	FetchDrawingBoard();
	FetchWordToGuessRoute();
	FetchWordToDisplayRoute();
	FetchMessagesRoute();
	PutWordToGuessRoute();
	PutMessageInChatRoute();

	m_app
		.port(18080)
		.multithreaded()
		.run();
}

void http::RouteManager::FetchWordRoute()
{
	CROW_ROUTE(m_app, "/fetchword")([this](const crow::request& request) {
        if (IsRequestAuthenticated(request)) return IsRequestAuthenticated(request).value();

        crow::response response;
        response.set_header("Content-Type", "application/json");

        try
        {
            std::string fetchedWord = m_storage.FetchWord();

            response.code = 200;
            response.body = crow::json::wvalue
            { {
                {"code", response.code},
                {"word", fetchedWord}
            } }.dump();

            return response;
        }
        catch (GarticException<CannotFetchWordException>& exception)
        {
            response.code = 500;
            response.body = crow::json::wvalue
            { {
                {"code", response.code},
                {"word", "N/A"},
                {"error", "Couldn't fetch word from database!"}
            } }.dump();

            return response;
        };

        // should never reach this point
        response.code = 500;
        response.body = crow::json::wvalue
        { {
            {"code", response.code},
            {"word", "N/A"},
            {"error", "Server unhandled error!"}
        } }.dump();

        return response;
	});
}

void http::RouteManager::FetchQuoteRoute()
{
	CROW_ROUTE(m_app, "/fetchquote")([this](const crow::request& request) {
        if (IsRequestAuthenticated(request)) return IsRequestAuthenticated(request).value();

        crow::response response;
        response.set_header("Content-Type", "application/json");

		try
		{
			std::string fetchedQuote = m_storage.FetchQuote();

            response.code = 200;
            response.body = crow::json::wvalue
            {{
                {"code", response.code},
                {"quote", fetchedQuote}
            }}.dump();

            return response;
		}
		catch (GarticException<CannotFetchQuoteException>& exception)
		{
            response.code = 500;
            response.body = crow::json::wvalue
            {{
                {"code", response.code},
                {"quote", "N/A"},
                {"error", "Couldn't fetch quote from database!"}
            }}.dump();

			return response;
		};

        // should never reach this point
        response.code = 500;
        response.body = crow::json::wvalue
        {{
            {"code", response.code},
            {"quote", "N/A"},
            {"error", "Server unhandled error!"}
        }}.dump();

        return response;
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
	CROW_ROUTE(m_app, "/fetchtopusers")([this](const crow::request& request) {
        if (IsRequestAuthenticated(request)) return IsRequestAuthenticated(request).value();

        crow::response response;
        response.set_header("Content-Type", "application/json");
        
        try
        {
            std::vector<crow::json::wvalue> top_users_json;

            UserVector topUsers = m_storage.FetchTop5Users();

            response.code = topUsers.size() == 5 ? 200 : 206;

            for (const auto& user : topUsers)
            {
                top_users_json.push_back(crow::json::wvalue{
                    { "username",     user.GetUsername()    },
                    { "points",       user.GetPoints()      },
                    { "games played", user.GetGamesPlayed() }
                });
            }

            response.body = crow::json::wvalue
            {{
                {"code", response.code},
                {"users", top_users_json}
            }}.dump();
            
            return response;
        }
        catch (GarticException<NotEnoughScoresRegisteredException>& exception)
        {
            response.code = 204;
            response.body = crow::json::wvalue
            {{
                {"code", response.code},
                {"users", std::vector<crow::json::wvalue>{}}
            }}.dump();
            
            return response;
        }
    });
}

void http::RouteManager::LoginRoute()
{
	CROW_ROUTE(m_app, "/login")([this](const crow::request& request) {
        if (IsRequestAuthenticated(request)) return IsRequestAuthenticated(request).value();
        
        crow::response response;

        response.code = 200;

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

std::optional<crow::response> http::RouteManager::IsRequestAuthenticated(const crow::request& request)
{
	std::optional<crow::response> returnResponse;
	char* password = request.url_params.get("password");
	char* username = request.url_params.get("username");
	crow::response response;
	std::regex regexFormatSHA256{ "[a-f0-9]{64}" };
	//std::regex regexFormatUsername{ "^[a-z]+[a-z0-9_-]*[a-z]+$" };
	std::regex regexFormatUsername{ "^[a-zA-Z]+[a-zA-Z0-9_-]*[a-zA-Z]+$" };


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
	/*if (std::strlen(password) != 64 || !std::regex_match(password, regexFormatSHA256))
	{
		response.code = 400;
		response.body = crow::json::wvalue
		({
			{"code", response.code},
			{"error", "invalid password format! (not hashed or bad hash)"}
			}).dump();

			return response;
	}*/

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
		
		return response;
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
		char* drawTime = request.url_params.get("drawTime");
		char* wordCount = request.url_params.get("wordCount");
		char* roundsNumber = request.url_params.get("roundsNumber");

		crow::response response;

		if (username == nullptr || drawTime == nullptr || wordCount == nullptr || roundsNumber == nullptr)
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

		m_gartic.GetLobby(std::string(username))->SetLobbyStatus(LobbyStatus::StartedGame);
		m_gartic.GetLobby(std::string(username))->SetDrawTime(std::atoi(drawTime));
		m_gartic.GetLobby(std::string(username))->SetRoundsNumber(std::atoi(roundsNumber));
		m_gartic.GetLobby(std::string(username))->SetWordCount(std::atoi(wordCount));

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}

void http::RouteManager::JoinLobbyRoute()
{
	CROW_ROUTE(m_app, "/joinlobby")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		char* code = request.url_params.get("code");

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
		std::string codeString(code);

		if (!m_storage.CheckCredentials(usernameString, passwordString))
		{
			// todo: log
			response.code = 401;
			response.body = crow::json::wvalue({
				{"no_user", false}
				}).dump();

				return response;
		}

		try
		{
			m_gartic.AddPlayerInLobby(usernameString, codeString);

			response.code = 200;
			response.body = crow::json::wvalue
			{ {
				{"code", response.code}
			} }.dump();

			return response;
		}
		catch (GarticException<LobbyDoesntExistException>& exception)
		{
			response.code = 500;
			response.body = crow::json::wvalue
			{ {
				{"code", response.code},
			} }.dump();

			return response;
		}

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
			settings_json.push_back(crow::json::wvalue{ {"roundsNumber", std::to_string(fetchedSettings.GetRoundsNumber())}});
			settings_json.push_back(crow::json::wvalue{ {"wordCount", std::to_string(fetchedSettings.GetWordCount())}});
			settings_json.push_back(crow::json::wvalue{ {"drawTime", std::to_string(fetchedSettings.GetDrawTime())}});
		}
		else
		{
			settings_json.push_back(crow::json::wvalue{ {"roundsNumber", "N/A"} });
			settings_json.push_back(crow::json::wvalue{ {"wordCount", "N/A"} });
			settings_json.push_back(crow::json::wvalue{ {"drawTime", "N/A"} });
		}

		return crow::json::wvalue{ settings_json };
		});
}

void http::RouteManager::FetchLobbyStatusRoute()
{
	CROW_ROUTE(m_app, "/fetchlobbystatus")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		LobbyStatus fetchedStatus = LobbyStatus();

		std::vector<crow::json::wvalue> status_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedStatus = m_gartic.GetLobby(usernameString)->GetLobbyStatus();

			std::string statusString = LobbyStatusWrapper::ToString(fetchedStatus);

			status_json.push_back(crow::json::wvalue{ {"lobby_status", statusString} });
		}
		else
		{
			status_json.push_back(crow::json::wvalue{ {"lobby_status", "N/A"} });
		}

		return crow::json::wvalue{ status_json };
		});
}

void http::RouteManager::LeaveLobbyRoute()
{
	CROW_ROUTE(m_app, "/leavelobby")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		crow::response response;

		if (!m_storage.CheckCredentials(usernameString, passwordString))
		{
			// todo: log
			response.code = 401;
			response.body = crow::json::wvalue({
				{"no_user", false}
				}).dump();

				return response;
		}

		try
		{
			m_gartic.GetLobby(usernameString)->RemoveUser(usernameString);
		}
		catch (...)
		{
			// todo: log
			response.code = 404;
			response.body = crow::json::wvalue({
				{"user_removed", false}
				}).dump();

				return response;
		}

		response.body = crow::json::wvalue({
			{"user_removed", true}
			}).dump();

			return response;
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
	CROW_ROUTE(m_app, "/fetchgamestatus")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		GameStatus fetchedStatus;

		std::vector<crow::json::wvalue> status_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			fetchedStatus = m_gartic.GetGame(usernameString)->GetGameStatus();

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

void http::RouteManager::FetchNWordsRoute()
{
	CROW_ROUTE(m_app, "/fetchnwords")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		std::string fetchedWord;

		std::vector<crow::json::wvalue> nWords_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			int numberOfWords = m_gartic.GetLobby(usernameString)->GetSettings().GetRoundsNumber();

			for (int i{ 0 }; i < numberOfWords; i++)
			{
				fetchedWord = m_storage.FetchWord();

				nWords_json.push_back(crow::json::wvalue{ {std::format("word_no{}", i), fetchedWord} });
			}
		}
		else
		{
			nWords_json.push_back(crow::json::wvalue{ {"n_words", "N/A"} });
		}

		return crow::json::wvalue{ nWords_json };
		});
}

void http::RouteManager::FetchDrawingBoard()
{
	CROW_ROUTE(m_app, "/fetchdrawingboard")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<crow::json::wvalue> drawingBoard_json;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			std::vector<DrawEvent*> drawEvents{ m_gartic.GetGame(usernameString)->GetBoard().GetAndDeleteEvents(usernameString)};

			int eventNo{ 0 };
			for (const auto& drawEvent : drawEvents)
			{
				drawingBoard_json.push_back(crow::json::wvalue{ {std::format("drawEvent_no{}", eventNo++), drawEvent->Serialize()}});
			}
		}
		else
		{
			drawingBoard_json.push_back(crow::json::wvalue{ {"drawingBoard", "N/A"} });
		}

		return crow::json::wvalue{ drawingBoard_json };
		});
}

void http::RouteManager::FetchWordToGuessRoute()
{
	CROW_ROUTE(m_app, "/fetchwordtoguess")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::vector<crow::json::wvalue> word_json;

		std::string usernameString(username);
		std::string passwordString(password);

		std::string wordToGuess;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			wordToGuess = m_gartic.GetGame(usernameString)->GetRound().GetWordToGuess();

			word_json.push_back(crow::json::wvalue{ {"word_to_guess", wordToGuess} });
		}
		else
		{
			word_json.push_back(crow::json::wvalue{ {"word_to_guess", "N/A"} });
		}

		return crow::json::wvalue{ word_json };
		});
}

void http::RouteManager::FetchWordToDisplayRoute()
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

			word_json.push_back(crow::json::wvalue{ {"word_to_display", wordToDisplay} });
		}
		else
		{
			word_json.push_back(crow::json::wvalue{ {"word_to_display", "N/A"} });
		}

		return crow::json::wvalue{ word_json };
		});
}

void http::RouteManager::FetchMessagesRoute()
{
	CROW_ROUTE(m_app, "/fetchmessages")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");

		std::vector<crow::json::wvalue> messages_json;

		std::string usernameString(username);
		std::string passwordString(password);

		std::vector<std::string> messages;

		if (m_storage.CheckCredentials(usernameString, passwordString))
		{
			messages = m_gartic.GetGame(usernameString)->GetChat().GetAndDeleteMessages(usernameString);

			for (int i{ 0 }; i < messages.size(); i++)
			{
				messages_json.push_back(crow::json::wvalue{ {std::format("message_no{}", i), messages[i]}});
			}
		}
		else
		{
			messages_json.push_back(crow::json::wvalue{ {"messages", "N/A"} });
		}

		return crow::json::wvalue{ messages_json };
		});
}

void http::RouteManager::PutWordToGuessRoute()
{
	CROW_ROUTE(m_app, "/putwordtoguess")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		char* wordToGuess = request.url_params.get("word");
		
		std::string usernameString(username);
		std::string passwordString(password);

		crow::response response;

		if (wordToGuess == nullptr)
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

		std::string wordToDiplayString(wordToGuess);
		m_gartic.GetGame(usernameString)->GetRound().SetWordToGuess(wordToDiplayString);

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}

void http::RouteManager::PutMessageInChatRoute()
{
	CROW_ROUTE(m_app, "/putmessageinchat")([this](const crow::request& request) {
		char* username = request.url_params.get("username");
		char* password = request.url_params.get("password");
		char* message = request.url_params.get("message");

		std::string usernameString(username);
		std::string passwordString(password);

		crow::response response;

		if (message == nullptr)
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

		std::string messageString(message);
		m_gartic.GetGame(usernameString)->GetChat().VerifyMessage(usernameString, messageString);

		response.body = crow::json::wvalue({
			{"put", true}
			}).dump();

			return response;
		});
}
