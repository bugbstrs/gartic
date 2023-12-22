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

	private:
		RoundType m_type;

		std::string m_wordToGuess;
		std::string m_wordToDisplay;

		Player* m_drawer;

		std::vector<Player*> m_players;
	};
}

