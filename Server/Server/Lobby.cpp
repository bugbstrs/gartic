#include "Lobby.h"

void http::Lobby::JoinLobby(Player&& newPlayer)
{
	m_players.push_back(std::move(newPlayer));
}

void http::Lobby::LeaveLobby(const Player& playerToLeave)
{
	if (auto it{ std::find(m_players.begin(), m_players.end(), playerToLeave) }; it != m_players.end())
	{
		m_players.erase(it);
	}

	throw UserDoesntExistException("The player is already not in the lobby!");
}

int http::Lobby::GetPlayersNumber() const noexcept
{
	return m_config.GetPlayersNumber();
}

int http::Lobby::GetDrawTime() const noexcept
{
	return m_config.GetDrawTime();
}

int http::Lobby::GetRoundsNumber() const noexcept
{
	return m_config.GetRoundsNumber();
}

http::Game* http::Lobby::StartGame()
{
	if (m_players.size() > 2)
	{
		return new Game(std::move(m_players));
	}

	throw NotEnoughPlayersException("There are not enough players to start a game!");
}
