#pragma once

#include "Round.h"
#include "Chat.h"
#include "Player.h"

import Timer;

namespace http
{
	class Game
	{
	public:
		Game(std::vector<Player>&& newPlayers);

		void NextSubRound();
		void NextRound();

		//Timer GetTimer() const noexcept;
		Round GetCurrRound() const noexcept;
		Chat GetChat() const noexcept;

	private:
		//Timer m_timer;

		int m_roundNumber;

		Round m_currRound;

		Chat m_chat;

		std::vector<Player> m_players;
	};
}

