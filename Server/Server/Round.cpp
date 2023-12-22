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

RoundType http::Round::GetRoundType() const noexcept
{
	return m_roundType;
}

const std::string& http::Round::GetWordToGuess() const noexcept
{
	return m_wordToGuess;
}

const std::string& http::Round::GetWordToDisplay() const noexcept
{
	return m_wordToDisplay;
}

Player* http::Round::GetDrawer()
{
	return m_drawer;
}

void http::Round::SetRoundType(RoundType newRoundType)
{
	m_roundType = newRoundType;
}

void http::Round::SetWordToGuess(const std::string& newWordToGuess)
{
	m_wordToGuess = newWordToGuess;
}

void http::Round::SetWordToDisplay(const std::string& newWordToDisplay)
{
	m_wordToDisplay = newWordToDisplay;
}

void http::Round::SetDrawer(Player* newDrawer)
{
	m_drawer = newDrawer;
}
