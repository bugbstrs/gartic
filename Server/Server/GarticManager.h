#pragma once

#include "Game.h"
#include "Lobby.h"

#include<string>
#include<memory>

using String = std::string;

namespace http
{
	class GarticManager
	{
	public:
		GarticManager() = default;

		void CreateLobby(const String& username);
		void CreateGame(const String& username);

		void AddPlayerInLobby(const String& username, const String& code);

		std::shared_ptr<Game> GetGame(const String& username) const noexcept;
		std::shared_ptr<Lobby> GetLobby(const String& username) const noexcept;

	private:
		std::shared_ptr<Game> m_game;

		std::shared_ptr<Lobby> m_lobby;
	};
}

