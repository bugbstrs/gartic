#pragma once

#include <vector>
#include <string>
#include <optional>
#include <cstdlib>
#include <ctime>

#include "User.h"
#include "Game.h"
#include "GameSettings.h"

//#include "UserDoesntExistException.h"
//#include "NotEnoughPlayersException.h"

namespace http
{
	class Lobby
	{
	public:
		Lobby() = default;

		~Lobby();

		void JoinLobby(User&& newPlayer);
		void LeaveLobby(const User& playerToLeave);

		const std::vector<User>& GetPlayers() const noexcept;
		const User* GetLeader() const noexcept;
		GameSettings GetSettings() const noexcept;
		const std::string& GetCode() const noexcept;

		void SetLeader(const User* newLeader);

		Game* StartGame();

	private:
		std::string GenerateCode();

	private:
		std::vector<User> m_players;

		User* m_leader;

		GameSettings m_settings;

		const std::string m_code = GenerateCode();
		const int kCodeLength{ 11 };
	};
}
