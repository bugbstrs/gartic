#include "GarticManager.h"

#include<algorithm>

import GarticExceptions;
using namespace http;

http::GarticManager::GarticManager(GarticStorage& storage):
	m_storage{ storage },
	m_checkActiveGamesTimer{ std::unique_ptr<Time>(new Time(10000)) }
{
	auto checkActiveCallback = [this]()
	{
		CheckActiveGames();
	};

	m_checkActiveGamesTimer->SetMethodToCall(checkActiveCallback);
}

void http::GarticManager::CreateLobby(const String& username)
{
	m_lobbys.push_back(std::make_shared<Lobby>(username));
}

void http::GarticManager::CreateGame(const String& username)
{
	for (const auto& lobby : m_lobbys)
	{
		if (lobby->GetUsers()[0]->GetUsername() == username)
		{
			m_games.push_back(lobby->StartGame(m_storage));
		}
	}
}

void http::GarticManager::AddPlayerInLobby(const String& username, const String& code)
{
	for (const auto& lobby : m_lobbys)
	{
		if (lobby->GetCode() == code)
		{
			if (lobby->GetLobbyStatus() == LobbyStatus::WaitingToStart) {
				lobby->AddUser(std::shared_ptr<User>(new User(username)));
				return;
			}
		}
	}

	throw GarticException<LobbyDoesntExistException>("GarticManager > AddPlayerInLobby(const String& username, const String& code): The searched lobby doesn't exist!");
}

std::shared_ptr<Game> http::GarticManager::GetGame(const String& username) const noexcept
{
	auto isInPlayers = [&username](const std::shared_ptr<Player> player)
	{
		if (player->GetName() == username)
		{
			player->SetActive();
			return true;
		}
		return false;
	};

	for (const auto& game : m_games)
	{
		if (auto players{ game->GetPlayers() };  std::find_if(players.begin(), players.end(), isInPlayers) != players.end())
		{
			return game;
		}
	}

	return {};
}

std::shared_ptr<Lobby> http::GarticManager::GetLobby(const String& username) const noexcept
{
	auto isInUsers = [&username](std::shared_ptr<User> user)
	{
		if (user->GetUsername() == username)
		{
			user->SetActive();
			return true;
		}
		return false;
	};

	for (const auto& lobby : m_lobbys)
	{
		if (auto users{ lobby->GetUsers() }; std::find_if(users.begin(), users.end(), isInUsers) != users.end())
		{
			return lobby;
		}
	}

	return {};
}

void http::GarticManager::CheckActiveGames()
{
	for (const auto& lobby : m_lobbys)
	{
		if (lobby->GetUsers().empty())
		{
			m_lobbys.erase(std::find(m_lobbys.begin(), m_lobbys.end(), lobby));
		}
	}
	for (const auto& game : m_games)
	{
		if (game->GetPlayers().empty())
		{
			m_games.erase(std::find(m_games.begin(), m_games.end(), game));
		}
	}

	m_checkActiveGamesTimer->Reset();
}
