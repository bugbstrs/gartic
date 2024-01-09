#pragma once

#include "Player.h"
#include "GameSettings.h"
#include "GameStatusEnum.h"
#include "RoundTypeEnum.h"
#include "Chat.h"
#include "DrawingBoard.h"
#include "Round.h"

#include <unordered_map>
#include <cmath>
#include <time.h> 

namespace http
{
	class Game
	{
	public:
		Game() = default;
		Game(std::vector<std::shared_ptr<Player>>&& newPlayers);

		~Game() = default;

		std::vector<std::shared_ptr<Player>>& GetPlayers() noexcept;
		GameStatus GetGameStatus() const noexcept;
		GameSettings GetSettings() const noexcept;
		std::shared_ptr<Time> GetTime() const noexcept;
		std::shared_ptr<Chat> GetChat() noexcept;
		int GetRoundNumber() const noexcept;
		std::shared_ptr<DrawingBoard> GetBoard() const noexcept;
		std::shared_ptr<Round> GetRound() const noexcept;
		std::string GetWordToGuess() const noexcept;

		void SetGameStatus(GameStatus newGameStatus);
		void SetRoundNumber(int newRoundNumber);
		void SetWordToGuess(const std::string& newWordToGuess);

		void NextRound();
		void RemovePlayer(const std::string& username);

	private:
		std::vector<std::shared_ptr<Player>> m_players;
		
		GameSettings m_settings;

		GameStatus m_gameStatus;

		std::shared_ptr<Time> m_remainingTime;

		std::shared_ptr<Chat> m_chat;

		int m_roundNumber;

		std::shared_ptr<Round> m_round;

		std::shared_ptr<DrawingBoard> m_board;

		std::string m_wordToGuess;
	};
}