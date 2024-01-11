#include "Round.h"

#include <random>

using namespace http;

http::Round::Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess,
				   GarticStorage& storage, std::shared_ptr<Time>& roundTime,
				   int numberOfWordsToChooseFrom, GameStatus& gameStatus, RoundType newType):
	m_players{ newPlayers },
	m_halfRoundTimer{ new Time(roundTime->GetDuration() / 2, false) },
	m_wordToDisplayTimer{ new Time(roundTime->GetDuration() / 6, false) },
	m_pickWordTimer{ new Time(15000) },
	m_roundTime{ roundTime },
	m_numberOfWordsToChooseFrom{ numberOfWordsToChooseFrom },
	m_wordToGuess{ wordToGuess },
	m_type{ newType },
	m_storage{ storage },
	m_gameStatus{ gameStatus },
	m_roundNumber { 1 }
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

	GetWordsToChooseFrom();
}

void http::Round::NextDrawer()
{
	m_gameStatus = GameStatus::PickingWord;

	std::string username = m_drawer->GetName();
	auto isDrawer = [&username](const std::shared_ptr<Player>& player) { return player->GetName() == username; };
	if (auto drawerIt = std::find_if(m_players.begin(), m_players.end(), isDrawer); drawerIt != m_players.end())
	{
		if (drawerIt == m_players.begin() + m_players.size() - 1)
		{
			++m_roundNumber;
			m_drawer = m_players[0];
		}
		else
		{
			++drawerIt;
			m_drawer = *drawerIt;
		}
	}

	m_halfRoundTimer->Stop();
	m_wordToDisplayTimer->Stop();
	m_roundTime->Stop();

	m_pickWordTimer->Reset();
	GetWordsToChooseFrom();
}

RoundType http::Round::GetRoundType() const noexcept
{
	return m_type;
}

int http::Round::GetRoundNumber() const noexcept
{
	return m_roundNumber;
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
			std::string fetchedWord = m_storage.FetchWord();
			while (m_wordsPicked.contains(fetchedWord))
			{
				fetchedWord = m_storage.FetchWord();
			}
			m_wordsPicked.insert(fetchedWord);
			m_wordsToChooseFrom.push_back(fetchedWord);
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

int http::Round::GetPickWordRemainingDuration()
{
	return m_pickWordTimer->GetRemainingTime();
}

bool http::Round::PickAWord(const std::string& pickedWord)
{
	if (std::find(m_wordsToChooseFrom.begin(), m_wordsToChooseFrom.end(), pickedWord) == m_wordsToChooseFrom.end())
	{
		return false;
	}

	m_wordsToChooseFrom.clear();
	m_wordToGuess = pickedWord;
	SetWordToDisplay(m_wordToGuess);
	m_pickWordTimer->Stop();
	m_roundTime->Reset();
	m_halfRoundTimer->Reset();
	
	m_gameStatus = GameStatus::Drawing;
	
	return true;
}

void http::Round::PickARandomWord()
{
	std::random_device				   rd;
	std::default_random_engine		   engine(rd());
	std::uniform_int_distribution<int> distribution(0, m_numberOfWordsToChooseFrom - 1);
	int randomNumber = distribution(engine);

	m_wordToGuess = m_wordsToChooseFrom[randomNumber];
	SetWordToDisplay(m_wordToGuess);
	m_wordsToChooseFrom.clear();
	m_roundTime->Reset();
	m_halfRoundTimer->Reset();

	m_gameStatus = GameStatus::Drawing;
}

void http::Round::StopAllTimers()
{
	m_halfRoundTimer->Stop();
	m_pickWordTimer->Stop();
	m_wordToDisplayTimer->Stop();
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

void http::Round::ActivateRevealLetters()
{
	RevealOneLetter();

	auto wrapper = [this]()
	{
		RevealOneLetter();
	};
	m_wordToDisplayTimer->Start();
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
