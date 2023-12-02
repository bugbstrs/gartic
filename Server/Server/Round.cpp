#include "Round.h"

http::Round::Round(int numberOfSubRounds, std::string&& wordToGuess) :
	m_playerToDraw{ 0 },
	m_currSubRound{ 0 },
	m_numberOfSubRounds{ numberOfSubRounds },
	m_wordToGuess{ wordToGuess },
	m_isLastSubRound{ false }
{
}

bool http::Round::IsLastSubRound() const noexcept
{
	return m_isLastSubRound;
}

void http::Round::NextSubRound()
{
	m_currSubRound += 1;
	m_playerToDraw += 1;

	if (m_currSubRound == m_numberOfSubRounds)
	{
		m_isLastSubRound = true;
	}

	// Word to guess should change here too
}
