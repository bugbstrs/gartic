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
		Round(RoundType newType, const String& newWordToGuess, const String& newWordToDisplay, Player* newDrawer, const std::vector<Player*>& newPlayers);

		void NextDrawer();

		RoundType GetRoundType() const noexcept;
		const String& GetWordToGuess() const noexcept;
		const String& GetWordToDisplay() const noexcept;
		Player* GetDrawer();

		void SetRoundType(RoundType newRoundType);
		void SetWordToGuess(const String& newWordToGuess);
		void SetWordToDisplay(const String& newWordToDisplay);
		void SetDrawer(Player* newDrawer);

	private:
		RoundType m_type;

		String m_wordToGuess;
		String m_wordToDisplay;

		Player* m_drawer;

		std::vector<Player*> m_players;
	};
}

