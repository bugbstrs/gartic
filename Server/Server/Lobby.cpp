#include "Lobby.h"

import GarticExceptions;
using namespace http;

http::Lobby::Lobby(const String& username)
{
	m_leader = std::make_shared<User>(User(username));
	m_users.push_back(m_leader);
	m_code = GenerateCode();
	m_lobbyStatus = LobbyStatus::WaitingToStart;
}

http::Lobby::~Lobby()
{}

void http::Lobby::AddUser(std::shared_ptr<User> newUser)
{
	auto removeUserCallback = [this](const std::string& username)
	{
		RemoveUser(username);
	};

	newUser->GetTime()->SetMethodToCall(removeUserCallback, newUser->GetUsername());
	m_users.push_back(newUser);
}

void http::Lobby::RemoveUser(const std::string& username)
{
	auto isUserToRemove = [&username](const std::shared_ptr<User> user) { return user->GetUsername() == username; };
	if (auto it = std::find_if(m_users.begin(), m_users.end(), isUserToRemove); it != m_users.end()) {
		if (it == m_users.begin() && m_users.size() > 1)
			m_leader = m_users[1];
		m_users.erase(it);
		return;
	}

	throw GarticException<UserDoesntExistException>("Lobby > LeaveLobby(const User&): The user is already not in the lobby!");
}

const std::vector<std::shared_ptr<User>>& http::Lobby::GetUsers() const noexcept
{
	return m_users;
}

std::shared_ptr<User> http::Lobby::GetLeader() const noexcept
{
	return m_leader;
}

GameSettings& http::Lobby::GetSettings() noexcept
{
	return m_settings;
}

const std::string& http::Lobby::GetCode() const noexcept
{
	return m_code;
}

LobbyStatus http::Lobby::GetLobbyStatus() const noexcept
{
	return m_lobbyStatus;
}

void http::Lobby::SetLeader(std::shared_ptr<User> newLeader)
{
	m_leader = newLeader;
}

void http::Lobby::SetLobbyStatus(LobbyStatus newLobbyStatus)
{
	m_lobbyStatus = newLobbyStatus;
}

void http::Lobby::SetDrawTime(int drawTime) noexcept
{
	m_settings.SetDrawTime(drawTime);
}

void http::Lobby::SetRoundsNumber(int roundsNumber) noexcept
{
	m_settings.SetRoundsNumber(roundsNumber);
}

void http::Lobby::SetWordCount(int wordCount) noexcept
{
	m_settings.SetWordCount(wordCount);
}

std::shared_ptr<http::Game> http::Lobby::StartGame()
{
	if (m_users.size() > 2)
	{
		std::vector<std::shared_ptr<Player>> playersVector;
		std::string currUsername;

		for (const auto& user : m_users)
		{
			currUsername = user->GetUsername();

			playersVector.push_back(std::make_shared<Player>(currUsername));
		}

		return std::make_shared<Game>(std::move(playersVector));
	}

	//throw GarticException<NotEnoughPlayersException>("Lobby > StartGame(): There are not enough players to start a game!");
	return {};
}

String http::Lobby::GenerateCode()
{
	std::string characters{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	size_t charactersLength{ characters.size() };

	srand(static_cast<unsigned int>(time(nullptr)));

	std::string randomCode;
	for (int i{ 0 }; i < kCodeLength; ++i) {
		int randomIndex = rand() % charactersLength;
		randomCode += characters[randomIndex];
	}

	return randomCode;
}
