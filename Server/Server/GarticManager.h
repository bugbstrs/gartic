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
		GarticManager() = delete;
		GarticManager(GarticStorage& storage);

		void CreateLobby(const String& username);
		void CreateGame(const String& username);

		void AddPlayerInLobby(const String& username, const String& code);

		std::shared_ptr<Game> GetGame(const String& username) const noexcept;
		std::shared_ptr<Lobby> GetLobby(const String& username) const noexcept;

	private:
		std::vector<std::shared_ptr<Game>> m_games;
		std::vector<std::shared_ptr<Lobby>> m_lobbys;

		GarticStorage& m_storage;

	private:
		std::unique_ptr<Time> m_checkActiveGamesTimer;
		void CheckActiveGames();
	};
}

