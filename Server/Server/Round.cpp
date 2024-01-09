#include "Round.h"

#include <random>

using namespace http;

http::Round::Round(const std::vector<std::shared_ptr<Player>>& newPlayers, int roundTime, RoundType newType):
	m_players{ newPlayers },
	m_halfRoundTimer{ new Time(roundTime / 2) },
	m_wordToDisplayTimer{ new Time(roundTime / 6) },
	m_type{ newType }
{
	auto wrapper = [this]()
	{
		ActivateRevealLetters();
	};
	m_halfRoundTimer->SetMethodToCall(wrapper);
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

std::shared_ptr<Player> http::Round::GetDrawer()
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

void http::Round::SetDrawer(std::shared_ptr<Player> newDrawer)
{
	m_drawer = newDrawer;
}

void http::Round::ActivateRevealLetters()
{
	RevealOneLetter();

	auto wrapper = [this]()
	{
		RevealOneLetter();
	};
	m_wordToDisplayTimer->Reset();
	m_wordToDisplayTimer->SetMethodToCall(wrapper);
}

void http::Round::RevealOneLetter()
{
	int lettersRevealed{ 0 };
	for (char c : m_wordToDisplay)
		if (c != ' ' && c != '_')
			++lettersRevealed;

	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	std::uniform_int_distribution<int> distribution(0, m_wordToDisplay.size() - lettersRevealed);
	int random_number = distribution(engine);

	m_wordToDisplay[random_number] = m_wordToGuess[random_number];

	m_wordToDisplayTimer->Reset();
}
