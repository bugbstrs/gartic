#include "RouteManager.h"
#include "Clear.h"
#include "Fill.h"
#include "KeepDraw.h"
#include "StartDraw.h"
#include "Undo.h"

#include <sstream>
#include <memory>
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
	LoginRoute();
	RegisterRoute();
	CheckBannedWordRoute();
    FetchProfileInfoRoute();
	CreateLobbyRoute();
	CreateGameRoute();
	JoinLobbyRoute();
	FetchCodeRoute();
	FetchUsersRoute();
	FetchSettingsRoute();
	FetchLobbyStatusRoute();
	LeaveLobbyRoute();
	LeaveGameRoute();
	FetchPlayersRoute();
	FetchGameStatusRoute();
	FetchRoundNumberRoute();
	FetchDrawingBoard();
    FetchWordsToGuessRoute();
	FetchWordToDisplayRoute();
	FetchMessagesRoute();
    FetchTimeRoute();
	PutWordToGuessRoute();
	PutMessageInChatRoute();
    PutEventsOnDrawingBoardRoute();
	SetSettingsRoute();

	m_app
		.port(18080)
		.multithreaded()
		.run();
}

void http::RouteManager::FetchWordRoute()
{
	auto FetchWordRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        try
        {
            std::string fetchedWord = m_storage.FetchWord();

            response.code = 200;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"word", fetchedWord}
            }.dump();

            response.end();
            return;
        }
        catch (GarticException<CannotFetchWordException>& exception)
        {
            response.code = 500;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"word", "N/A"},
                {"error", "Couldn't fetch word from database!"}
            }.dump();

            response.end();
            return;
        };

        // should never reach this point
        response.code = 500;
        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"word", "N/A"},
            {"error", "Server unhandled error!"}
        }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/fetchword")(FetchWordRouteFunction);
}

void http::RouteManager::FetchQuoteRoute()
{
	auto FetchQuoteRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

		try
		{
			std::string fetchedQuote = m_storage.FetchQuote();

            response.code = 200;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"quote", fetchedQuote}
            }.dump();

            response.end();
            return;
		}
		catch (GarticException<CannotFetchQuoteException>& exception)
		{
            response.code = 500;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"quote", "N/A"},
                {"error", "Couldn't fetch quote from database!"}
            }.dump();

            response.end();
            return;
		};

        // should never reach this point
        response.code = 500;
        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"quote", "N/A"},
            {"error", "Server unhandled error!"}
        }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/fetchquote")(FetchQuoteRouteFunction);
}

void http::RouteManager::LoginRoute()
{
	auto LoginRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }
    
        response.body = crow::json::wvalue
        {
            {"code", response.code}
        }.dump();

        response.end();
    };

    CROW_ROUTE(m_app, "/login")(LoginRouteFunction);
}

void http::RouteManager::RegisterRoute()
{
	auto RegisterRouteFunction = [&](const crow::request& request, crow::response& response) {
		String password = request.url_params.get("password");
		String username = request.url_params.get("username");

		response = IsRequestAuthenticated(request);

        if (response.code == 400)
        {
            response.end();
            return;
        }

		try
		{
			m_storage.CreateUser(username, password);
            
            response.code = 201;
            response.body = crow::json::wvalue
            {
                {"code", response.code}
            }.dump();

            response.end();
            return;
		}
		catch (GarticException<UserAlreadyExistsException>& exception)
		{
			response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "An user with this username already exists!"}
            }.dump();

            response.end();
            return;
		}
        //response.end();
    };

    CROW_ROUTE(m_app, "/register").methods(crow::HTTPMethod::POST)(RegisterRouteFunction);
}

void http::RouteManager::CheckBannedWordRoute()
{
	auto CheckBannedWordRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

		char* word = request.url_params.get("name");

        if (word == nullptr)
        {
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The word to be checked was not provided"}
            }.dump();
            response.end();
            return;
        }

		bool checkBannedWord = m_storage.CheckBannedWord(String(word));
        
        response.code = 200;
        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"banned", checkBannedWord}
        }.dump();
        
		response.end();
	};

    CROW_ROUTE(m_app, "/bannedword")(CheckBannedWordRouteFunction);
}

void http::RouteManager::FetchProfileInfoRoute()
{
    auto FetchProfileInfoRouteFunction = [&](const crow::request& request, crow::response& response)
        {
            response = IsRequestAuthenticated(request);

            if (response.code != 200)
            {
                response.end();
                return;
            }

            String username = request.url_params.get("username");

            std::vector<std::pair<int, int>> profileInfo;
            std::vector<crow::json::wvalue> historyJson;
            try
            {
                profileInfo = m_storage.FetchAllHistoriesOf(username);
                for (const auto& info : profileInfo) {
                    crow::json::wvalue currentMatch;
                    currentMatch["rank"] = info.first;
                    currentMatch["points"] = info.second;
                    historyJson.emplace_back(currentMatch);
                }
            }
            catch (...)
            {
                response.code = 404;
                response.body = crow::json::wvalue
                {
                    {"code", response.code},
                    {"error", "The user doesn't have a history!"}
                }.dump();

                response.end();
                return;
            }

            response.body = crow::json::wvalue
            {
                {"info", historyJson}
            }.dump();

            response.end();
        };

    CROW_ROUTE(m_app, "/fetchprofileinfo")(FetchProfileInfoRouteFunction);
}

crow::response http::RouteManager::IsRequestAuthenticated(const crow::request& request)
{
	char* password = request.url_params.get("password");
	char* username = request.url_params.get("username");
	
    std::regex regexFormatSHA256{ "[a-f0-9]{64}" };
	//std::regex regexFormatUsername{ "^[a-z]+[a-z0-9_-]*[a-z]+$" };
	std::regex regexFormatUsername{ "^[a-zA-Z]+[a-zA-Z0-9_-]*[a-zA-Z]+$" };

	crow::response response;
    response.set_header("Content-Type", "application/json");

	if (password == nullptr || username == nullptr)
	{
		response.code = 400;
		response.body = crow::json::wvalue
		{
			{"code", response.code},
			{"error", "Username or password not provided"}
		}.dump();

		return response;
	}

	// length of SHA256 hash when converted to hex string
	/*if (std::strlen(password) != 64 || !std::regex_match(password, regexFormatSHA256))
	{
		response.code = 400;
		response.body = crow::json::wvalue
		{
			{"code", response.code},
			{"error", "invalid password format! (not hashed or bad hash)"}
		}.dump();

		return response;
	}*/

	if (!std::regex_match(username, regexFormatUsername))
	{
		response.code = 400;
		response.body = crow::json::wvalue
		{
			{"code", response.code},
			{"error", "invalid username format! ((username format description))"}
		}.dump();

		return response;
	}

	bool foundCredentials = m_storage.CheckCredentials(String(username), String(password));

	if (!foundCredentials)
	{
		response.code = 401;
		response.body = crow::json::wvalue
		{
			{"code", response.code},
			{"error", "unauthorized"}
		}.dump();
		
		return response;
	}

	return response;
}

void http::RouteManager::CreateLobbyRoute()
{
	auto CreateLobbyRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		m_gartic.CreateLobby(username);

		response.body = crow::json::wvalue
        {
			{"code", response.code}
	    }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/createlobby").methods(crow::HTTPMethod::POST)(CreateLobbyRouteFunction);
}

void http::RouteManager::CreateGameRoute()
{
	auto CreateGameRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		m_gartic.CreateGame(std::string(username));

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }

    	m_gartic.GetLobby(std::string(username))->SetLobbyStatus(LobbyStatus::StartedGame);

		response.body = crow::json::wvalue
        {
            {"code", response.code}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/creategame").methods(crow::HTTPMethod::POST)(CreateGameRouteFunction);
}

void http::RouteManager::JoinLobbyRoute()
{
	auto JoinLobbyRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");
		char* code = request.url_params.get("code");

        if (code == nullptr)
        {
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "No lobby code provided!"}
            }.dump();

            response.end();
            return;
        }

        String codeString = code;

		try
		{
            m_gartic.AddPlayerInLobby(username, codeString);

			response.code = 200;
			response.body = crow::json::wvalue
			{
				{"code", response.code}
			}.dump();

			response.end();
            return;
		}
		catch (GarticException<LobbyDoesntExistException>& exception)
		{
			response.code = 404;
			response.body = crow::json::wvalue
			{
				{"code", response.code},
                {"error", "The lobby was not found!"}
			}.dump();

            response.end();
            return;
		}
	};

    // put?
    CROW_ROUTE(m_app, "/joinlobby").methods(crow::HTTPMethod::POST)(JoinLobbyRouteFunction);
}

void http::RouteManager::FetchCodeRoute()
{
	auto FetchCodeRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }

    	std::string fetchedCode = m_gartic.GetLobby(username)->GetCode();
        
        response.body = crow::json::wvalue
        {
            {"code", fetchedCode}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchcode")(FetchCodeRouteFunction);
}

void http::RouteManager::FetchUsersRoute()
{
	auto FetchUsersRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		std::vector<std::shared_ptr<User>> fetchedUsers;
		std::vector<crow::json::wvalue> usersJSONArray;

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }

        fetchedUsers = m_gartic.GetLobby(username)->GetUsers();
		
        for (const auto& user : fetchedUsers)
            usersJSONArray.push_back(user->GetUsername());
        
        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"users", usersJSONArray}
        }.dump();

		response.end();
    };

    CROW_ROUTE(m_app, "/fetchusers")(FetchUsersRouteFunction);
}

void http::RouteManager::SetSettingsRoute()
{
	auto SetSettingsRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		char* roundsNumber = request.url_params.get("roundsnumber");
		char* wordCount = request.url_params.get("wordcount");
		char* drawTime = request.url_params.get("drawtime");

        if (roundsNumber == nullptr)
        {
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "Number of rounds not provided!"}
            }.dump();

            response.end();
            return;
        }
        if (wordCount == nullptr)
        {
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "Number of words not provided!"}
            }.dump();

            response.end();
            return;
        }
        if (drawTime == nullptr)
        {
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "Drawing time not provided!"}
            }.dump();

            response.end();
            return;
        }

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }

		m_gartic.GetLobby(username)->GetSettings().SetWordCount(std::stoi(wordCount));
		m_gartic.GetLobby(username)->GetSettings().SetRoundsNumber(std::stoi(roundsNumber));
		m_gartic.GetLobby(username)->GetSettings().SetDrawTime(std::stoi(drawTime));

		response.code = 200;
		response.body = crow::json::wvalue
        {
			{"code", response.code}
	    }.dump();

		response.end();
    };
    
    CROW_ROUTE(m_app, "/setsettings").methods(crow::HTTPMethod::POST)(SetSettingsRouteFunction);
}

void http::RouteManager::FetchSettingsRoute()
{
	auto FetchSettingsRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }

		GameSettings fetchedSettings{ m_gartic.GetLobby(std::string(username))->GetSettings() };

        crow::json::wvalue settingsJSON
        {
            {"roundsNumber", fetchedSettings.GetRoundsNumber()},
            {"wordCount", fetchedSettings.GetWordCount()},
            {"drawTime", fetchedSettings.GetDrawTime()}
        };

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"settings", settingsJSON}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchsettings")(FetchSettingsRouteFunction);
}

void http::RouteManager::FetchLobbyStatusRoute()
{
	auto FetchLobbyStatusRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetLobby(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a lobby!"}
            }.dump();

            response.end();
            return;
        }
		
        LobbyStatus fetchedStatus = m_gartic.GetLobby(username)->GetLobbyStatus();

		std::string statusString = LobbyStatusWrapper::ToString(fetchedStatus);

		response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"status", statusString}
        }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/fetchlobbystatus")(FetchLobbyStatusRouteFunction);
}

void http::RouteManager::LeaveLobbyRoute()
{
	auto LeaveLobbyRouteFunction = [&](const crow::request& request, crow::response& response)
    {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		try
		{
            if (!m_gartic.GetLobby(username))
            {
                response.code = 403;
                response.body = crow::json::wvalue
                {
                    {"code", response.code},
                    {"error", "The user is not in a lobby!"}
                }.dump();

                response.end();
                return;
            }
			
            m_gartic.GetLobby(username)->RemoveUser(username);
            
            response.code = 200;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"removed", true}
            }.dump();

            response.end();
            return;
		}
		catch (...)
		{
			// todo: log
			response.code = 404;
			response.body = crow::json::wvalue
            {
                {"code", response.code},
				{"removed", false},
                {"error", "The user was not found!"}
            }.dump();

            response.end();
            return;
		}

        response.end();
	};

    CROW_ROUTE(m_app, "/leavelobby")(LeaveLobbyRouteFunction);
}

void http::RouteManager::FetchPlayersRoute()
{
	auto FetchPlayersRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

        std::vector<std::shared_ptr<Player>> fetchedPlayers = m_gartic.GetGame(username)->GetPlayers();
        std::shared_ptr<Player> drawer = m_gartic.GetGame(username)->GetRound()->GetDrawer();

		std::vector<crow::json::wvalue> playersJSON;

        int drawerIndex{ 0 };
        bool drawerFound{ false };
		for (auto player : fetchedPlayers)
		{
            crow::json::wvalue playerJSON;
            playerJSON["name"] = player->GetName();
            playerJSON["points"] = player->GetPoints();
            playerJSON["guessed"] = player->GetGuessed();
            playersJSON.emplace_back(playerJSON);

            if (player->GetName() != drawer->GetName())
            {
                if (!drawerFound)
                    ++drawerIndex;
            }
            else
            {
                drawerFound = true;
            }
		}

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"players", playersJSON},
            {"drawer index", drawerIndex}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchplayers")(FetchPlayersRouteFunction);
}

void http::RouteManager::FetchGameStatusRoute()
{
	auto FetchGameStatusRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

        GameStatus fetchedStatus = m_gartic.GetGame(username)->GetGameStatus();

	    std::string statusString = GameStatusWrapper::ToString(fetchedStatus);

	    response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"status", statusString}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchgamestatus")(FetchGameStatusRouteFunction);
}

void http::RouteManager::FetchRoundNumberRoute()
{
	auto FetchRoundNumberRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

        std::string roundNumber = m_gartic.GetGame(username)->GetRoundNumberString();

		response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"round", roundNumber}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchroundnumber")(FetchRoundNumberRouteFunction);
}

void http::RouteManager::FetchDrawingBoard()
{
	auto FetchDrawingBoardFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

        std::vector<std::string> events{ m_gartic.GetGame(username)->GetBoard()->GetAndDeleteEvents(username) };
        std::vector<crow::json::wvalue> eventsJSON;
        for (const auto& drawEvent : events)
            eventsJSON.emplace_back(drawEvent);

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"events", eventsJSON}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchdrawingboard")(FetchDrawingBoardFunction);
}

void http::RouteManager::FetchWordsToGuessRoute()
{
	auto FetchWordsToGuessRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

		std::vector<std::string> wordsToGuess = m_gartic.GetGame(username)->GetRound()->GetWordsToChooseFrom();
        std::vector<crow::json::wvalue> wordsToGuessJSON;
        for (const auto& word : wordsToGuess)
            wordsToGuessJSON.emplace_back(word);

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"words", wordsToGuessJSON}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchwordstoguess")(FetchWordsToGuessRouteFunction);
}

void http::RouteManager::FetchWordToDisplayRoute()
{
	auto FetchWordToDisplayRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

        std::string wordToDisplay = m_gartic.GetGame(username)->GetRound()->GetWordToDisplay(username);

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"word", wordToDisplay}
        }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/fetchwordtodisplay")(FetchWordToDisplayRouteFunction);
}

void http::RouteManager::FetchMessagesRoute()
{
	auto FetchMessagesRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");
		std::vector<crow::json::wvalue> messagesJSON;

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

		std::vector<std::string> messages = m_gartic.GetGame(username)->GetChat()->GetAndDeleteMessages(username);

		for (const auto& message : messages)
            messagesJSON.push_back(message);

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"messages", messagesJSON}
        }.dump();

		response.end();
	};

    CROW_ROUTE(m_app, "/fetchmessages")(FetchMessagesRouteFunction);
}

void http::RouteManager::FetchTimeRoute()
{
    auto FetchTimeFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The game has not started yet!"}
            }.dump();

            response.end();
            return;
        }

        int gameTime = m_gartic.GetGame(username)->GetTime();

        response.body = crow::json::wvalue
        {
            {"code", response.code},
            {"time", gameTime}
        }.dump();

        response.end();
    };

    CROW_ROUTE(m_app, "/fetchtime")(FetchTimeFunction);
}

void http::RouteManager::LeaveGameRoute()
{
	auto LeaveGameRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

		try
		{
            if (!m_gartic.GetGame(username))
            {
                response.code = 403;
                response.body = crow::json::wvalue
                {
                    {"code", response.code},
                    {"error", "The user is not in a game!"}
                }.dump();

                response.end();
                return;
            }

			m_gartic.GetGame(username)->RemovePlayer(username);

            response.code = 200;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"removed", true}
            }.dump();

            response.end();
            return;
		}
		catch (...)
		{
			// todo: log
			response.code = 404;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"removed", false},
                {"error", "Player not found!"}
            }.dump();

            response.end();
            return;
		}
        
        response.end();
	};

    CROW_ROUTE(m_app, "/leavegame")(LeaveGameRouteFunction);
}

void http::RouteManager::PutWordToGuessRoute()
{
	auto PutWordToGuessRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");
		char* wordToGuess = request.url_params.get("word");

		if (wordToGuess == nullptr)
		{
			// todo: log
			response.code = 400;
			response.body = crow::json::wvalue
            {
				{"code", response.code},
                {"error", "The word to be guessed was not provided!"}
			}.dump();

            response.end();
            return;
		}

		std::string wordToGuessString(wordToGuess);

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }
		
        m_gartic.GetGame(username)->GetRound()->PickAWord(wordToGuessString);

		response.body = crow::json::wvalue
        {
			{"code", response.code}
	    }.dump();

	    response.end();
	};

    CROW_ROUTE(m_app, "/putwordtoguess").methods(crow::HTTPMethod::POST)(PutWordToGuessRouteFunction);
}

void http::RouteManager::PutMessageInChatRoute()
{
	auto PutMessageInChatRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");
		char* message = request.url_params.get("message");

		if (message == nullptr)
		{
			// todo: log
            response.code = 400;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The message to be posted was not provided!"}
            }.dump();

            response.end();
            return;
		}

		std::string messageString(message);

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }

		m_gartic.GetGame(username)->GetChat()->VerifyMessage(username, messageString);

        response.body = crow::json::wvalue
        {
            {"code", response.code}
        }.dump();

        response.end();
	};

    CROW_ROUTE(m_app, "/putmessageinchat").methods(crow::HTTPMethod::POST)(PutMessageInChatRouteFunction);
}

void http::RouteManager::PutEventsOnDrawingBoardRoute()
{
    auto PutMessageInChatRouteFunction = [&](const crow::request& request, crow::response& response) {
        response = IsRequestAuthenticated(request);

        if (response.code != 200)
        {
            response.end();
            return;
        }

        String username = request.url_params.get("username");

        if (!m_gartic.GetGame(username))
        {
            response.code = 403;
            response.body = crow::json::wvalue
            {
                {"code", response.code},
                {"error", "The user is not in a game!"}
            }.dump();

            response.end();
            return;
        }


        crow::json::rvalue eventsJson = crow::json::load(request.url_params.get("events"));

        for (const auto& item : eventsJson)
            m_gartic.GetGame(username)->GetBoard()->Draw(username, std::string(item));

        response.body = crow::json::wvalue
        {
            {"code", response.code}
        }.dump();

        response.end();
    };

    CROW_ROUTE(m_app, "/putdraweventsindrawingboard").methods(crow::HTTPMethod::POST)(PutMessageInChatRouteFunction);
}
