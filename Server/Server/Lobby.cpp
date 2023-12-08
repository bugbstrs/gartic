#include "Lobby.h"

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

	throw UserDoesntExistException("The player is already not in the lobby!");
}

std::vector<User> http::Lobby::GetPlayers() const noexcept
{
	return m_players;
}

User* http::Lobby::GetLeader() const noexcept
{
	return m_leader;
}

GameSettings http::Lobby::GetSettings() const noexcept
{
	return m_settings;
}

std::string http::Lobby::GetCode() const noexcept
{
	return m_code;
}

void http::Lobby::SetLeader(const User* newLeader)
{
	m_leader = new User(*newLeader);
}

void http::Lobby::SetCode(const std::string& newCode)
{
	m_code = newCode;
}

http::Game* http::Lobby::StartGame()
{
	if (m_players.size() > 2)
	{
		return new Game(m_players);
	}

	throw NotEnoughPlayersException("There are not enough players to start a game!");
}

std::string http::Lobby::GenerateCode()
{
	const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	const int charactersLength = characters.size();

	srand(static_cast<unsigned int>(time(nullptr)));

	std::string randomCode;
	for (int i = 0; i < kCodeLength; ++i) {
		int randomIndex = rand() % charactersLength;
		randomCode += characters[randomIndex];
	}

	return randomCode;
}
