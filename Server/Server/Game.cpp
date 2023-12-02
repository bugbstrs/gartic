#include "Game.h"

using namespace http;

Game::Game(std::vector<Player>&& newPlayers) :
	//m_timer{ Timer() },
	m_roundNumber{ 1 },
	//m_currRound{ Round() },
	m_players{ std::move(newPlayers) }
	//m_chat{ Chat() }
{
}

void Game::NextSubRound()
{
	if (!m_currRound.IsLastSubRound())
	{
		m_currRound.NextSubRound();
	}
	else
	{
		NextRound();
	}
}

void Game::NextRound()
{
	m_roundNumber += 1;

	m_currRound = Round();
}

//Timer Game::GetTimer() const noexcept
//{
//	return m_timer;
//}

Round Game::GetCurrRound() const noexcept
{
	return m_currRound;
}

Chat Game::GetChat() const noexcept
{
	return m_chat;
}
