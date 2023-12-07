#pragma once

#include <vector>
#include <string>
#include <array>
#include <optional>

#include "User.h"
#include "Game.h"
#include "GameSettings.h"

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

		std::vector<User> GetPlayers() const noexcept;
		User* GetLeader() const noexcept;
		GameSettings GetSettings() const noexcept;
		std::string GetCode() const noexcept;

		void SetLeader(const User* newLeader);
		int SetCode(int newCode);

		Game* StartGame();

	private:
		std::vector<User> m_players;

		User* m_leader;

		GameSettings m_settings;

		std::string m_code;
	};
}
