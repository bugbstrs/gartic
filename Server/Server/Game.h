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

		const std::vector<std::shared_ptr<Player>>& GetPlayers() const noexcept;
		GameStatus GetGameStatus() const noexcept;
		GameSettings GetSettings() const noexcept;
		Time GetTime() const noexcept;
		Chat& GetChat() noexcept;
		int GetRoundNumber() const noexcept;
		DrawingBoard GetBoard() const noexcept;
		Round& GetRound() noexcept;

		void SetGameStatus(GameStatus newGameStatus);
		void SetRoundNumber(int newRoundNumber);
		void SetDrawingBoard(DrawingBoard newDrawingBoard);

		void NextRound();
		void RemovePlayer(const std::string& username);

	private:
		std::vector<std::shared_ptr<Player>> m_players;
		
		GameSettings m_settings;

		GameStatus m_gameStatus;

		Time m_remainingTime;

		Chat m_chat;

		int m_roundNumber;

		Round m_round;

		DrawingBoard m_board;
	};
}