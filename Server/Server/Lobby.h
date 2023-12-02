#pragma once

#include <vector>

#include <array>
#include <optional>

#include "LobbyConfig.h"
#include "Player.h"
#include "Game.h"

#include "UserDoesntExistException.h"
#include "NotEnoughPlayersException.h"

namespace http
{
	class Lobby
	{
	public:
		Lobby() = default;

		void JoinLobby(Player&& newPlayer);
		void LeaveLobby(const Player& playerToLeave);

		int GetPlayersNumber() const noexcept;
		int GetDrawTime() const noexcept;
		int GetRoundsNumber() const noexcept;

		Game* StartGame();

	private:
		LobbyConfig m_config;

		std::vector<Player> m_players;
	};
}
