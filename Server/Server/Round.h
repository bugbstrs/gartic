#pragma once

#include<string>

#include "RoundTypeEnum.h"
#include "Player.h"

namespace http
{
	class Round
	{
	public:
		Round() = delete;
		Round(std::vector<std::shared_ptr<Player>>& newPlayers, std::string& wordToGuess, int roundTime, RoundType newType = RoundType::Normal);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		const std::string& GetWordToGuess() const noexcept;
		const std::string& GetWordToDisplay() const noexcept;
		std::shared_ptr<Player> GetDrawer();

		void SetRoundType(RoundType newRoundType);
		void SetWordToGuess(const std::string& newWordToGuess);
		void SetWordToDisplay(const std::string& newWordToDisplay);
		void SetDrawer(std::shared_ptr<Player> newDrawer);

		void ActivateRevealLetters();
		void RevealOneLetter();

	private:
		RoundType m_type;

		std::string& m_wordToGuess;
		std::string m_wordToDisplay;

		Time* m_wordToDisplayTimer;
		Time* m_halfRoundTimer;

		std::shared_ptr<Player> m_drawer;

		std::vector<std::shared_ptr<Player>>& m_players;
	};
}

