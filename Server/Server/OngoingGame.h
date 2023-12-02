#pragma once

#include "Lobby.h"
#include "Game.h"

namespace http
{
	class OngoingGame
	{
	public:
		void AddLobby(Lobby& newLobby);
		void AddGame(Game& newGame);

		Lobby* GetLobby() const noexcept;
		Game* GetGame() const noexcept;

	private:
		Lobby* m_lobby;
		Game* m_game;
	};
}

