#include "Round.h"

using namespace http;

http::Round::Round(RoundType newType, const String &newWordToGuess, const String &newWordToDisplay, Player *newDrawer, const std::vector<Player *> &newPlayers, int roundTime):
	m_type{newType},
	m_wordToGuess{newWordToGuess},
	m_wordToDisplay{newWordToDisplay},
	m_drawer{std::move(newDrawer)},
	m_players{newPlayers},
	m_halfRoundTimer{new Time(roundTime / 2)},
	m_wordToDisplayTimer{nullptr}//new Time(roundTime / 6)}
{
	auto activateRevealLettersCallback = [this]()
	{
		ActivateRevealLetters();
	};

	m_halfRoundTimer->SetMethodToCall(activateRevealLettersCallback);
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
	return m_type;
}

const String& http::Round::GetWordToGuess() const noexcept
{
	return m_wordToGuess;
}

const String& http::Round::GetWordToDisplay() const noexcept
{
	return m_wordToDisplay;
}

Player* http::Round::GetDrawer()
{
	return m_drawer;
}

void http::Round::SetRoundType(RoundType newRoundType)
{
	m_type = newRoundType;
}

void http::Round::SetWordToGuess(const String& newWordToGuess)
{
	m_wordToGuess = newWordToGuess;
}

void http::Round::SetWordToDisplay(const String& newWordToDisplay)
{
	m_wordToDisplay = newWordToDisplay;
}

void http::Round::SetDrawer(Player* newDrawer)
{
	m_drawer = newDrawer;
}

void http::Round::ActivateRevealLetters()
{

}

void http::Round::RevealOneLetter()
{

}
