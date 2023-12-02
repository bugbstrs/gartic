#pragma once

#include <vector>

#include <array>
#include <optional>

#include "LobbyConfig.h"
#include "Player.h"

namespace http
{
	class Lobby
	{
	public:
		Lobby();

		void JoinLobby();
		void LeaveLobby();

		bool StartGame();

	private:
		LobbyConfig m_config;

		std::vector<Player> m_players;
	};
}
