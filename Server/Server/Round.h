#pragma once

#include<string>

#include "RoundTypeEnum.h"
#include "Player.h"

namespace http
{
	class Round
	{
	public:
		Round() = default;
		Round(RoundType newType, const std::string& newWordToGuess, const std::string& newWordToDisplay, Player* newDrawer, const std::vector<Player*>& newPlayers);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		const std::string& GetWordToGuess() const noexcept;
		const std::string& GetWordToDisplay() const noexcept;
		Player* GetDrawer();

		void SetRoundType(RoundType newRoundType);
		void SetWordToGuess(const std::string& newWordToGuess);
		void SetWordToDisplay(const std::string& newWordToDisplay);
		void SetDrawer(Player* newDrawer);

	private:
		RoundType m_type;

		std::string m_wordToGuess;
		std::string m_wordToDisplay;

		Player* m_drawer;

		std::vector<Player*> m_players;
	};
}

