#include "GarticManager.h"

#include<algorithm>

import GarticExceptions;
using namespace http;

http::GarticManager::GarticManager(GarticStorage& storage):
	m_storage{ storage }
{}

void http::GarticManager::CreateLobby(const String& username)
{
	m_lobby = std::make_shared<Lobby>(username);
}

void http::GarticManager::CreateGame(const String& username)
{
	if (m_lobby->GetUsers()[0]->GetUsername() == username)
	{
		m_game = m_lobby->StartGame(m_storage);
	}
}

void http::GarticManager::AddPlayerInLobby(const String& username, const String& code)
{
	if (m_lobby->GetCode() == code)
	{
		m_lobby->AddUser(std::shared_ptr<User>(new User(username)));
		return;
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

	if (auto players{ m_game->GetPlayers() };  std::find_if(players.begin(), players.end(), isInPlayers) != players.end())
	{
		return m_game;
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

	if (auto users{ m_lobby->GetUsers() }; std::find_if(users.begin(), users.end(), isInUsers) != users.end())
	{
		return m_lobby;
	}
	return {};
}
