#include "Round.h"

using namespace http;

http::Round::Round(RoundType newType, const std::string& newWordToGuess, const std::string& newWordToDisplay, Player* newDrawer, const std::vector<Player*>& newPlayers) :
	m_type{ newType },
	m_wordToGuess{ newWordToGuess },
	m_wordToDisplay{ newWordToDisplay },
	m_drawer{ std::move(newDrawer) },
	m_players{ newPlayers }
{
}

void http::Round::NextDrawer()
{
	if (m_drawer == nullptr)
	{
		return;
	}

	auto drawerIt = std::find(m_players.rbegin(), m_players.rend(), m_drawer);

	if (drawerIt == m_players.rbegin())
	{
		m_drawer = m_players[0];
	}
	else
	{
		m_drawer = m_players[m_players.rbegin() - drawerIt];
	}
}
