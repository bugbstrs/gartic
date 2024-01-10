#pragma once

#include <vector>
#include <string>
#include <optional>
#include <cstdlib>
#include <ctime>
#include "User.h"
#include "Game.h"
#include "LobbyStatusEnum.h"
#include "GameSettings.h"
#include "GarticDatabase.h"

namespace http
{
	class Lobby
	{
	public:
		Lobby() = default;
		Lobby(const std::string& username);

		~Lobby();

		void AddUser(std::shared_ptr<User> newUser);
		void RemoveUser(const std::string& username);

		const std::vector<std::shared_ptr<User>>& GetUsers() const noexcept;
		std::shared_ptr<User> GetLeader() const noexcept;
		GameSettings& GetSettings() noexcept;
		const std::string& GetCode() const noexcept;
		LobbyStatus GetLobbyStatus() const noexcept;

		void SetLeader(std::shared_ptr<User> newLeader);
		void SetLobbyStatus(LobbyStatus newLobbyStatus);

		void SetDrawTime(int drawTime) noexcept;
		void SetRoundsNumber(int roundsNumber) noexcept;
		void SetWordCount(int wordCount) noexcept;

		std::shared_ptr<Game> StartGame(GarticStorage& storage);

	private:
		std::string GenerateCode();

	private:
		const int kCodeLength{ 11 };
		std::vector<std::shared_ptr<User>> m_users;

		std::shared_ptr<User> m_leader;

		GameSettings m_settings;

		LobbyStatus m_lobbyStatus;

		std::string m_code;
	};
}
