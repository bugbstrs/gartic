#include "Round.h"

#include <random>

using namespace http;

http::Round::Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess,
				   int roundTime, RoundType newType):
	m_players{ newPlayers },
	m_halfRoundTimer{ new Time(roundTime / 2) },
	m_wordToDisplayTimer{ new Time(roundTime / 6) },
	m_wordToGuess{ wordToGuess },
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
	auto drawerIt = std::find(m_players.rbegin(), m_players.rend(), m_drawer);

	if (drawerIt == m_players.rbegin())
	{
		++m_roundNumber;
		m_drawer = m_players[0];
	}
	else
	{
		++drawerIt;
		m_drawer = *drawerIt;
	}

	m_halfRoundTimer->Reset();
}

RoundType http::Round::GetRoundType() const noexcept
{
	return m_type;
}

int http::Round::GetRoundNumber() const noexcept
{
	return m_roundNumber;
}

std::string& http::Round::GetWordToGuess()
{
	return m_wordToGuess;
}

const std::string& http::Round::GetWordToDisplay() const noexcept
{
	return m_wordToDisplay;
}

std::shared_ptr<Player> http::Round::GetDrawer() const noexcept
{
	return m_drawer;
}

void http::Round::SetRoundType(RoundType newRoundType)
{
	m_type = newRoundType;
}

void http::Round::SetWordToGuess(const std::string& newWordToGuess)
{
	m_wordToGuess = newWordToGuess;
}

void http::Round::SetWordToDisplay(const std::string& newWordToDisplay)
{
	m_wordToDisplay = newWordToDisplay;
}

void http::Round::SetDrawer(std::shared_ptr<Player> newDrawer)
{
	m_drawer = newDrawer;
}

void http::Round::SetRoundNumber(int newRoundNumber)
{
	m_roundNumber = newRoundNumber;
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
