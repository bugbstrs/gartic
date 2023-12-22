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
		Game(std::vector<Player*>&& newPlayers);

		~Game() = default;

		const std::vector<Player*>& GetPlayers() const noexcept;
		GameStatus GetStatus() const noexcept;
		GameSettings GetSettings() const noexcept;
		Time GetTime() const noexcept;
		Chat GetChat() const noexcept;
		int GetRoundNumber() const noexcept;
		DrawingBoard GetBoard() const noexcept;
		Round GetRound() const noexcept;

		void SetGameStatus(GameStatus newGameStatus);
		void SetRoundNumber(int newRoundNumber);
		void SetDrawingBoard(DrawingBoard newDrawingBoard);

		void NextRound();
		void RemovePlayer(const std::string& username);

	private:
		std::vector<Player*> m_players;
		
		GameSettings m_settings;

		GameStatus m_status;

		Time m_remainingTime;

		Chat m_chat;

		int m_roundNumber;

		Round m_round;

		DrawingBoard m_board;
	};
}