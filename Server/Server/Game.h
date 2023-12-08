#pragma once

#include "Player.h"
#include "GameSettings.h"
#include "GameStatusEnum.h"
#include "SpecialRoundsEnum.h"
#include "Chat.h"
#include "Round.h"
#include "DrawingBoard.h"

namespace http
{
	class Game
	{
	public:
		Game(std::vector<Player>&& newPlayers);

		~Game() = default;

		std::vector<Player> GetPlayers() const noexcept;
		Player* GetDrawer() const noexcept;
		GameSettings GetSettings() const noexcept;
		GameStatus GetStatus() const noexcept;
		Time GetTime() const noexcept;
		Chat GetChat() const noexcept;
		int GetRoundNumber() const noexcept;
		Round GetCurrRound() const noexcept;
		DrawingBoard GetBoard() const noexcept;
		std::string GetWordToGuess() const noexcept;
		std::string GetWordToDisplay() const noexcept;

		void SetGameStatus(GameStatus newGameStatus);
		void SetRoundNumber(int newRoundNumber);
		void SetDrawingBoard(DrawingBoard newDrawingBoard);
		void SetWordToGuess(const std::string& newWordToGuess);

		void NextDrawer();
		void NextRound();
		void RemovePlayer(const std::string& username);

	private:
		std::vector<Player*> m_players;

		Player* m_drawer;

		GameSettings m_settings;

		GameStatus m_status;

		Time m_remainingTime;

		Chat m_chat;

		int m_roundNumber;

		SpecialRound m_specialRoundType;

		Round m_currRound;

		DrawingBoard m_board;

		std::string m_wordToGuess;

		std::string m_wordToDisplay;
	};
}

