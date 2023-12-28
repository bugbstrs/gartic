#pragma once

#include <vector>
#include <string>
#include <optional>
#include <cstdlib>
#include <ctime>

#include "User.h"
#include "Game.h"
#include "GameSettings.h"

namespace http
{
	class Lobby
	{
	public:
		Lobby() = default;
		Lobby(const String& username);

		~Lobby();

		void AddUser(std::shared_ptr<User> newUser);
		void RemoveUser(std::shared_ptr<User> userToLeave);

		const std::vector<std::shared_ptr<User>>& GetUsers() const noexcept;
		std::shared_ptr<User> GetLeader() const noexcept;
		const GameSettings& GetSettings() const noexcept;
		const std::string& GetCode() const noexcept;

		void SetLeader(std::shared_ptr<User> newLeader);

		std::shared_ptr<Game> StartGame();

	private:
		const String& GenerateCode();

	private:
		std::vector<std::shared_ptr<User>> m_users;

		std::shared_ptr<User> m_leader;

		GameSettings m_settings;

		const String m_code{ GenerateCode() };
		const int kCodeLength{ 11 };
	};
}
