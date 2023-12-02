#include "Round.h"

http::Round::Round(int numberOfRounds, std::string&& wordToGuess) :
	m_playerToDraw{ 0 },
	m_currSubRound{ 0 },
	m_numberOfRounds{ numberOfRounds },
	m_wordToGuess{ wordToGuess },
	m_isLastSubRound{ false }
{
}

void http::Round::NextSubRound()
{
	m_currSubRound += 1;
	m_playerToDraw += 1;

	if (m_currSubRound == m_numberOfRounds)
	{
		m_isLastSubRound = true;
	}

	// Word to guess should change here too
}
