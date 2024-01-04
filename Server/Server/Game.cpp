#include "Game.h"

using namespace http;

Game::Game(std::vector<Player*>&& newPlayers) :
	m_players{ std::move(newPlayers) },
	m_gameStatus { GameStatus::Waiting },
	m_lobbyStatus { LobbyStatus::WaitingToStart },
	m_remainingTime { Time() },
	m_chat { Chat(m_players) },
	m_roundNumber { 0 },
	m_board { DrawingBoard(m_players) },
	m_round {}
{
	for (auto& player : m_players)
	{
		auto removePlayerCallback = std::bind(&Game::RemovePlayer, this, player->GetName());
		player->GetTime().SetMethodToCall(removePlayerCallback);
	}
}

const std::vector<Player*>& http::Game::GetPlayers() const noexcept
{
	return m_players;
}

GameSettings http::Game::GetSettings() const noexcept
{
	return m_settings;
}

GameStatus http::Game::GetGameStatus() const noexcept
{
	return m_gameStatus;
}

LobbyStatus http::Game::GetLobbyStatus() const noexcept
{
	return m_lobbyStatus;
}

Time http::Game::GetTime() const noexcept
{
	return m_remainingTime;
}

DrawingBoard http::Game::GetBoard() const noexcept
{
	return m_board;
}

Round http::Game::GetRound() const noexcept
{
	return m_round;
}

void http::Game::SetGameStatus(GameStatus newGameStatus)
{
	m_gameStatus = newGameStatus;
}

void http::Game::SetLobbyStatus(LobbyStatus newLobbyStatus)
{
	m_lobbyStatus = newLobbyStatus;
}

void http::Game::SetRoundNumber(int newRoundNumber)
{
	m_roundNumber = newRoundNumber;
}

void http::Game::SetDrawingBoard(DrawingBoard newDrawingBoard)
{
	m_board = newDrawingBoard;
}

Chat Game::GetChat() const noexcept
{
	return m_chat;
}

int http::Game::GetRoundNumber() const noexcept
{
	return m_roundNumber;
}

void Game::NextRound()
{
	m_roundNumber += 1;

	if (m_roundNumber == m_settings.GetRoundsNumber() - 1)
	{
		/*std::random_device				   rd;
		std::default_random_engine		   engine(rd());
		auto							   count = isWordsEntity ? m_db.count<WordsEntity>() : m_db.count<QuotesEntity>();
		std::uniform_int_distribution<int> distribution(0, count - 1);*/

        // remove srand
		srand(static_cast<unsigned int>(time(0)));

		int randomRoundIndex = rand();

		/*m_specialRoundType = (RoundType)randomRoundIndex;

		m_status = GameStatus::SpecialRound;*/
	}
}

void http::Game::RemovePlayer(const std::string& username)
{
	int indexToRemove = -1;

	for (int index = 0; index < m_players.size(); index++)
	{
		if (m_players[index]->GetName() == username)
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