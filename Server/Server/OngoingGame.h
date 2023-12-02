#pragma once

#include "Lobby.h"
#include "Game.h"

namespace http
{
	class OngoingGame
	{
	public:
		OnGoingGame() = delete;

		void AddLobby(const Lobby& newLobby);
		void AddGame(const Game& newGame);

		Lobby* GetLobby() const noexcept;
		Game* GetGame() const noexcept;

	private:
		Lobby* m_lobby;
		Game* m_game;
	};
}

