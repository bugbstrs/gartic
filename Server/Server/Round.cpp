#include "Round.h"

#include <random>

using namespace http;

http::Round::Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess,
				   int roundTime, int numberOfWordsToChooseFrom, RoundType newType):
	m_players{ newPlayers },
	m_halfRoundTimer{ new Time(roundTime / 2, false) },
	m_wordToDisplayTimer{ new Time(roundTime / 6, false) },
	m_pickWordTimer{ new Time(15000) },
	m_numberOfWordsToChooseFrom{ numberOfWordsToChooseFrom },
	m_wordToGuess{ wordToGuess },
	m_type{ newType }
{
	m_drawer = m_players[0];

	auto revealLettersWrapper = [this]()
	{
		ActivateRevealLetters();
	};
	auto pickARandomWordWrapper = [this]()
	{
		PickARandomWord();
	};

	m_halfRoundTimer->SetMethodToCall(revealLettersWrapper);
	m_pickWordTimer->SetMethodToCall(pickARandomWordWrapper);
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

std::vector<std::string> http::Round::GetWordsToChooseFrom()
{
	if(m_wordsToChooseFrom.empty())
		for (int index{ 0 }; index < m_numberOfWordsToChooseFrom; ++index)
		{
			// TODO: Get words from data base
		}

	return m_wordsToChooseFrom;
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

bool http::Round::PickAWord(const std::string& pickedWord)
{
	if (std::find(m_wordsToChooseFrom.begin(), m_wordsToChooseFrom.end(), pickedWord) == m_wordsToChooseFrom.end())
		return false;

	m_wordsToChooseFrom.clear();
	m_wordToGuess = pickedWord;
	SetWordToDisplay(m_wordToGuess);
	m_pickWordTimer->Stop();
	return true;
}

void http::Round::PickARandomWord()
{
	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	std::uniform_int_distribution<int> distribution(0, m_numberOfWordsToChooseFrom);
	int randomNumber = distribution(engine);

	m_wordToGuess = m_wordsToChooseFrom[randomNumber];
	SetWordToDisplay(m_wordToGuess);
	m_wordsToChooseFrom.clear();
}

void http::Round::SetWordToDisplay(const std::string& word)
{
	m_wordToDisplay.clear();
	for (const auto& c : word)
	{
		if (c == ' ')
			m_wordToDisplay += ' ';
		else
			m_wordToDisplay += '_';
	}
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
	int randomNumber = distribution(engine);

	m_wordToDisplay[randomNumber] = m_wordToGuess[randomNumber];

	m_wordToDisplayTimer->Reset();
}
