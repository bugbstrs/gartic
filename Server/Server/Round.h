#pragma once

#include<string>

#include "RoundTypeEnum.h"
#include "Player.h"

using String = std::string;

namespace http
{
	class Round
	{
	public:
		Round() = default;
		Round(const std::vector<std::shared_ptr<Player>>& newPlayers, int roundTime, RoundType newType = RoundType::Normal);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		const String& GetWordToGuess() const noexcept;
		const String& GetWordToDisplay() const noexcept;
		std::shared_ptr<Player> GetDrawer();

		void SetRoundType(RoundType newRoundType);
		void SetWordToGuess(const String& newWordToGuess);
		void SetWordToDisplay(const String& newWordToDisplay);
		void SetDrawer(std::shared_ptr<Player> newDrawer);

		void ActivateRevealLetters();
		void RevealOneLetter();

	private:
		RoundType m_type;

		String m_wordToGuess;
		String m_wordToDisplay;

		Time* m_wordToDisplayTimer;
		Time* m_halfRoundTimer;

		std::shared_ptr<Player> m_drawer;

		std::vector<std::shared_ptr<Player>> m_players;
	};
}

