#include "OngoingGame.h"

void http::OngoingGame::AddLobby(Lobby& newLobby) 
{
	m_lobby = &newLobby;
}

void http::OngoingGame::AddGame(Game& newGame) 
{
	m_game = &newGame;
}

http::Lobby* http::OngoingGame::GetLobby() const noexcept
{
	return m_lobby;
}

http::Game* http::OngoingGame::GetGame() const noexcept
{
	return m_game;
}
