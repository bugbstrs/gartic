#include "Lobby.h"

import GarticExceptions;
using namespace http;

http::Lobby::Lobby(const String& username)
{
	m_leader = std::make_shared<User>(User(username));
	m_users.push_back(m_leader);
}

http::Lobby::~Lobby()
{}

void http::Lobby::AddUser(std::shared_ptr<User> newUser)
{
	m_users.push_back(newUser);
}

void http::Lobby::RemoveUser(std::shared_ptr<User> userToLeave)
{
	if (auto it{ std::find(m_users.begin(), m_users.end(), userToLeave) }; it != m_users.end())
	{
		m_users.erase(it);
        return;
	}	

	throw GarticException<UserDoesntExistException>("Lobby > LeaveLobby(const User&): The player is already not in the lobby!");
}

const std::vector<std::shared_ptr<User>>& http::Lobby::GetUsers() const noexcept
{
	return m_users;
}

std::shared_ptr<User> http::Lobby::GetLeader() const noexcept
{
	return m_leader;
}

const GameSettings& http::Lobby::GetSettings() const noexcept
{
	return m_settings;
}

const std::string& http::Lobby::GetCode() const noexcept
{
	return m_code;
}

void http::Lobby::SetLeader(std::shared_ptr<User> newLeader)
{
	m_leader = newLeader;
}

std::shared_ptr<http::Game> http::Lobby::StartGame()
{
	if (m_users.size() > 2)
	{
		std::vector<Player*> playersVector;
		std::string currUsername;

		for (const auto& user : m_users)
		{
			currUsername = user->GetUsername();

			playersVector.push_back(new Player(currUsername));
		}

		return std::make_shared<Game>(std::move(playersVector));
	}

	//throw GarticException<NotEnoughPlayersException>("Lobby > StartGame(): There are not enough players to start a game!");
	return {};
}

const String& http::Lobby::GenerateCode()
{
	std::string characters{ "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz" };
	size_t charactersLength{ characters.size() };

	srand(static_cast<unsigned int>(time(nullptr)));

	std::string randomCode;
	for (int i{ 0 }; i < kCodeLength; ++i) {
		int randomIndex = rand() % charactersLength;
		randomCode += characters[randomIndex];
	}

	return characters;
}
