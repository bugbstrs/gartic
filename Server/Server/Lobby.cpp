#include "Lobby.h"

import GarticExceptions;
using namespace http;

http::Lobby::~Lobby()
{
	delete m_leader;
}

void http::Lobby::JoinLobby(User&& newPlayer)
{
	m_players.push_back(std::move(newPlayer));
}

void http::Lobby::LeaveLobby(const User& playerToLeave)
{
	if (auto it{ std::find(m_players.begin(), m_players.end(), playerToLeave) }; it != m_players.end())
	{
		m_players.erase(it);
	}
/*
	throw GarticException<UserDoesntExistException>("Lobby > LeaveLobby(const User&): The player is already not in the lobby!");*/
}

const std::vector<User>& http::Lobby::GetPlayers() const noexcept
{
	return m_players;
}

const User* http::Lobby::GetLeader() const noexcept
{
	return m_leader;
}

GameSettings http::Lobby::GetSettings() const noexcept
{
	return m_settings;
}

const std::string& http::Lobby::GetCode() const noexcept
{
	return m_code;
}

void http::Lobby::SetLeader(const User* newLeader)
{
	m_leader = new User(*newLeader);
}

http::Game* http::Lobby::StartGame()
{
	if (m_players.size() > 2)
	{
		std::vector<Player*> playersVector;
		std::string currUsername;

		for (const auto& player : m_players)
		{
			currUsername = player.GetUsername();

			playersVector.push_back(new Player(currUsername));
		}

		return new Game(std::move(playersVector));
	}

	//throw GarticException<NotEnoughPlayersException>("Lobby > StartGame(): There are not enough players to start a game!");
	return {};
}

std::string http::Lobby::GenerateCode()
{
	std::string characters{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	size_t charactersLength{ characters.size() };

	srand(static_cast<unsigned int>(time(nullptr)));

	std::string randomCode;
	for (int i = 0; i < kCodeLength; ++i) {
		int randomIndex = rand() % charactersLength;
		randomCode += characters[randomIndex];
	}

	return characters;
}
