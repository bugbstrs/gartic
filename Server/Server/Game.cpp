#include "Game.h"

using namespace http;

Game::Game(std::vector<Player>&& newPlayers) :
	m_players{ std::move(newPlayers) },
	m_drawer { m_players[0] },
	m_status { GameStatus::Waiting },
	m_remainingTime { Time() },
	m_chat { Chat() },
	m_roundNumber { 0 },
	m_specialRoundType { SpecialRound::None },
	m_drawingBoard { DrawingBoard() },
	m_wordToGuess { "" },
	m_wordToDisplay { "" }
{
	for (const auto& player : m_players)
	{
		player.GetTime().SetMethodToCall(RemovePlayer());
	}
}

std::vector<Player> http::Game::GetPlayers() const noexcept
{
	return m_players;
}

Player* http::Game::GetDrawer() const noexcept
{
	return m_drawer;
}

GameSettings http::Game::GetSettings() const noexcept
{
	return m_settings;
}

GameStatus http::Game::GetStatus() const noexcept
{
	return m_status;
}

Time http::Game::GetTime() const noexcept
{
	return m_time;
}

Round Game::GetCurrRound() const noexcept
{
	return m_currRound;
}

DrawingBoard http::Game::GetBoard() const noexcept
{
	return m_board;
}

std::string http::Game::GetWordToGuess() const noexcept
{
	return m_wordToGuess;
}

std::string http::Game::GetWordToDisplay() const noexcept
{
	return m_wordToDisplay;
}

void http::Game::SetGameStatus(GameStatus newGameStatus)
{
	m_status = newGameStatus;
}

void http::Game::SetRoundNumber(int newRoundNumber)
{
	m_roundNumber = newRoundNumber;
}

void http::Game::SetDrawingBoard(DrawingBoard newDrawingBoard)
{
	m_board = newDrawingBoard;
}

void http::Game::SetWordToGuess(const std::string& newWordToGuess)
{
	m_wordToGuess = newWordToGuess;
}

Chat Game::GetChat() const noexcept
{
	return m_chat;
}

int http::Game::GetRoundNumber() const noexcept
{
	return m_roundNumber;
}

void http::Game::NextDrawer()
{
	if (m_drawer == nullptr)
	{
		return;
	}

	auto drawerIt = std::find(m_players.begin(), m_players.end(), m_drawer);

	if (drawerIt == m_players.rbegin())
	{
		NextRound();
		m_drawer = m_players[0];
	}
	else
	{
		m_drawer = m_players[m_players.begin() + drawerIt];
	}
}

void Game::NextRound()
{
	m_roundNumber += 1;

	if (m_roundNumber == m_settings.GetRoundsNumber() - 1)
	{
		std::random_device				   rd;
		std::default_random_engine		   engine(rd());
		auto							   count = isWordsEntity ? m_db.count<WordsEntity>() : m_db.count<QuotesEntity>();
		std::uniform_int_distribution<int> distribution(0, count - 1);

		int randomRoundIndex = distribution(engine);

		m_specialRoundType = randomRoundIndex;

		m_status = GameStatus::SpecialRound;
	}
}


void http::Game::RemovePlayer(const std::string& username)
{
	int indexToRemove = -1;

	for (int index = 0; index < m_players.size(); index++)
	{
		if (player.GetName() == username)
		{
			indexToRemove = index;
		}
	}

	if (indexToRemove == -1)
	{
		return;
	}

	m_players.erase(m_players.begin() + indexToRemove);
}

bool http::Game::IsCloseEnough(const std::string& currGuess)
{
	auto tokenize = [](const std::string& str, std::unordered_map<std::string, int>& wordFrequency) {
		size_t start = 0, end = 0;
		while ((end = str.find(' ', start)) != std::string::npos) {
			std::string word = str.substr(start, end - start);
			wordFrequency[word]++;
			start = end + 1;
		}
		std::string lastWord = str.substr(start);
		wordFrequency[lastWord]++;
		};

	std::unordered_map<std::string, int> freq1, freq2;
	tokenize(str1, freq1);
	tokenize(str2, freq2);

	double dotProduct = 0.0;
	for (const auto& entry : freq1) 
	{
		dotProduct += entry.second * freq2[entry.first];
	}

	double mag1 = 0.0, mag2 = 0.0;
	for (const auto& entry : freq1) 
	{
		mag1 += std::pow(entry.second, 2);
	}
	
	for (const auto& entry : freq2) 
	{
		mag2 += std::pow(entry.second, 2);
	}

	double similarity = dotProduct / (std::sqrt(mag1) * std::sqrt(mag2));
	
	return similarity >= kThreshold;
}
