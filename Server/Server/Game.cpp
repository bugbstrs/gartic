#include "Game.h"

#include <ranges>

import GarticExceptions;
using namespace http;

Game::Game(std::vector<std::shared_ptr<Player>>&& newPlayers, GarticStorage& storage, GameSettings& newGameSettings) :
	m_wordToGuess{ std::string{} },
	m_players{ std::move(newPlayers) },
	m_gameStatus { GameStatus::PickingWord },
	m_settings{ newGameSettings },
	m_gameTime{ std::shared_ptr<Time>{ new Time(m_settings.GetDrawTime() * 1000, false) } },
	m_chat { std::shared_ptr<Chat>{ new Chat(m_players, m_wordToGuess, m_gameTime, m_gameStatus, storage) } },
	m_board{ std::shared_ptr<DrawingBoard>{ new DrawingBoard(m_players) } },
	m_round{ std::shared_ptr<Round>{ new Round(m_players, m_wordToGuess, storage, m_gameTime, m_settings.GetWordCount(), m_gameStatus) } },
	m_storage { storage }
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

std::string http::Game::GetRoundNumberString() const noexcept
{
	return std::format("{} of {}", m_round->GetRoundNumber(), m_settings.GetRoundsNumber());
}

std::shared_ptr<Chat> Game::GetChat() noexcept
{
	return m_chat;
}

static inline bool GreaterForPlayers(const std::shared_ptr<Player> player1, const std::shared_ptr<Player> player2)
{
	return player1->GetPoints() > player2->GetPoints();
}

void Game::NextRound()
{
	float averageGuessTime = .0;

	for (auto& player : m_players | std::views::filter([&](const auto& p) { return m_round->GetDrawer() != p; }))
	{
		if (!player->GetGuessed())
		{
			player->AddPoints(-50);
			player->SetTimeWhenGuessed(m_gameTime->GetDuration() / 1000);
		}

		averageGuessTime += player->GetTimeWhenGuessed();
		player->SetGuessed(false);
	}

	averageGuessTime /= (m_players.size() - 1);

	if (m_round->GetDrawer())
	{
		if (averageGuessTime == m_gameTime->GetDuration() / 1000)
			m_round->GetDrawer()->AddPoints(-100);
		else
			m_round->GetDrawer()->AddPoints((m_gameTime->GetDuration() / 1000 - averageGuessTime) * 100 / (m_gameTime->GetDuration() / 1000));
	}

	m_round->NextDrawer();

	// Game is finished
	if (m_round->GetRoundNumber() == m_settings.GetRoundsNumber() + 1)
	{
		EndGame();
	}
}

void http::Game::RemovePlayer(const std::string& username)
{
	auto isPlayerToRemove = [&username](const std::shared_ptr<Player> player) { return player->GetName() == username; };
	if (auto it = std::ranges::find_if(m_players, isPlayerToRemove); it != m_players.end())
	{
		if (*it == m_round->GetDrawer())
		{
			NextRound();
		}

		m_players.erase(it);

		if (m_players.size() == 1)
			EndGame();
		return;
	}

	throw GarticException<PlayerDoesntExistException>("Game > LeaveGame(const Player&): The player is already not in the game!");
}

void http::Game::EndGame()
{
	m_gameStatus = GameStatus::Finished;
	m_gameTime->Stop();
	m_round->StopAllTimers();

	std::sort(m_players.begin(), m_players.end(), GreaterForPlayers);

	m_storage.PopulateGameHistoryEntity(m_players);
}
