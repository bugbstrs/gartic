#include "Game.h"

import GarticExceptions;
using namespace http;

Game::Game(std::vector<std::shared_ptr<Player>>&& newPlayers) :
	m_players{ std::move(newPlayers) },
	m_gameStatus { GameStatus::Waiting },
	m_remainingTime{ std::shared_ptr<Time>{ new Time(5) } },
	m_chat { std::shared_ptr<Chat>{ new Chat(m_players, m_wordToGuess) } },
	m_roundNumber { 0 },
	m_board{ std::shared_ptr<DrawingBoard>{ new DrawingBoard(m_players) } },
	m_round{ std::shared_ptr<Round>{ new Round(m_players, m_wordToGuess, m_settings.GetDrawTime()) } }
{
	/*for (auto& player : m_players)
	{
		auto removePlayerCallback = std::bind(&Game::RemovePlayer, this, player->GetName());
		player->GetTime().SetMethodToCall(removePlayerCallback);
	}*/
}

std::vector<std::shared_ptr<Player>>& http::Game::GetPlayers() noexcept
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

std::shared_ptr<Time> http::Game::GetTime() const noexcept
{
	return m_remainingTime;
}

std::shared_ptr<DrawingBoard> http::Game::GetBoard() const noexcept
{
	return m_board;
}

std::shared_ptr<Round> http::Game::GetRound() const noexcept
{
	return m_round;
}

void http::Game::SetGameStatus(GameStatus newGameStatus)
{
	m_gameStatus = newGameStatus;
}

void http::Game::SetRoundNumber(int newRoundNumber)
{
	m_roundNumber = newRoundNumber;
}

std::shared_ptr<Chat> Game::GetChat() noexcept
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
	auto isPlayerToRemove = [&username](const std::shared_ptr<Player> player) { return player->GetName() == username; };
	if (auto it = std::find_if(m_players.begin(), m_players.end(), isPlayerToRemove); it != m_players.end())
	{
		m_players.erase(it);
		return;
	}

	throw GarticException<PlayerDoesntExistException>("Game > LeaveGame(const Player&): The player is already not in the game!");
}