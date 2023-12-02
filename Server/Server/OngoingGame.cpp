#include "OngoingGame.h"

void http::OngoingGame::AddLobby(const Lobby& newLobby): m_lobby{newLobby}
{
}

void http::OngoingGame::AddGame(const Game& newGame) : m_game{newGame}
{
}

Lobby* http::OngoingGame::GetLobby() const noexcept
{
	return m_lobby;
}

Game* http::OngoingGame::GetGame() const noexcept
{
	return m_game;
}
