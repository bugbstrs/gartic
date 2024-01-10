#include "Game.h"

import GarticExceptions;
using namespace http;

Game::Game(std::vector<std::shared_ptr<Player>>&& newPlayers, GarticStorage& storage) :
	m_players{ std::move(newPlayers) },
	m_gameStatus { GameStatus::PickingWord },
	m_gameTime{ std::shared_ptr<Time>{ new Time(m_settings.GetDrawTime() * 1000, false) } },
	m_chat { std::shared_ptr<Chat>{ new Chat(m_players, m_wordToGuess, m_gameTime) } },
	m_board{ std::shared_ptr<DrawingBoard>{ new DrawingBoard(m_players) } },
	m_round{ std::shared_ptr<Round>{ new Round(m_players, m_wordToGuess, storage, m_gameTime, m_settings.GetWordCount(), m_gameStatus) } }
{
	auto removePlayerCallback = [this](const std::string& username)
	{
		RemovePlayer(username);
	};
	for (auto& player : m_players)
	{
		player->GetTime()->SetMethodToCall(removePlayerCallback, player->GetName());
	}

	auto nextRoundCallback = [this]()
	{
		NextRound();
	};
	m_gameTime->SetMethodToCall(nextRoundCallback);
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

int http::Game::GetTime() const noexcept
{
	switch (m_gameStatus)
	{
	case GameStatus::PickingWord:
		return m_round->GetPickWordRemainingDuration() / 1000;
		break;
	case GameStatus::Drawing:
		return m_gameTime->GetRemainingTime() / 1000;
		break;
	case GameStatus::Finished:
		return 0;
		break;
	}
}

std::shared_ptr<DrawingBoard> http::Game::GetBoard() const noexcept
{
	return m_board;
}

std::shared_ptr<Round> http::Game::GetRound() const noexcept
{
	return m_round;
}

std::string http::Game::GetWordToGuess() const noexcept
{
	return m_wordToGuess;
}

std::shared_ptr<Chat> Game::GetChat() noexcept
{
	return m_chat;
}

void Game::NextRound()
{
	float averageGuessTime = .0;
	for (auto& player : m_players)
	{
		if (m_round->GetDrawer() == player)
		{
			continue;
		}

		if(!player->GetGuessed())
		{ 
			player->AddPoints(-50);
			player->SetTimeWhenGuessed(m_gameTime->GetDuration() / 1000);
		}

		averageGuessTime += player->GetTimeWhenGuessed();
		
		player->SetGuessed(false);
	}

	averageGuessTime /= (m_players.size() - 1);

	if (averageGuessTime == m_gameTime->GetDuration() / 1000)
		m_round->GetDrawer()->AddPoints(-100);
	else
		m_round->GetDrawer()->AddPoints((m_gameTime->GetDuration() / 1000 - averageGuessTime) * 100 / (m_gameTime->GetDuration() / 1000));


	m_round->NextDrawer();

	// Game is finished
	if (m_round->GetRoundNumber() == m_settings.GetRoundsNumber() + 1)
	{
		m_gameStatus = GameStatus::Finished;
		m_gameTime->Stop();
		// TODO: stop all timers
	}


	/*if (m_round->GetRoundNumber() == m_settings.GetRoundsNumber() - 1)
	{
		std::random_device				   rd;
		std::default_random_engine		   engine(rd());
		auto							   count = isWordsEntity ? m_db.count<WordsEntity>() : m_db.count<QuotesEntity>();
		std::uniform_int_distribution<int> distribution(0, count - 1);

        // remove srand
		srand(static_cast<unsigned int>(time(0)));

		int randomRoundIndex = rand();

		m_specialRoundType = (RoundType)randomRoundIndex;

		m_status = GameStatus::SpecialRound;
	}*/


	m_gameTime->Reset();
}

void http::Game::RemovePlayer(const std::string& username)
{
	auto isPlayerToRemove = [&username](const std::shared_ptr<Player> player) { return player->GetName() == username; };
	if (auto it = std::find_if(m_players.begin(), m_players.end(), isPlayerToRemove); it != m_players.end())
	{
		// TODO: Check if it is drawer


		m_players.erase(it);
		return;
	}

	throw GarticException<PlayerDoesntExistException>("Game > LeaveGame(const Player&): The player is already not in the game!");
}