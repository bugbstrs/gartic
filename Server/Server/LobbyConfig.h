#pragma once

#include <fstream>

namespace http
{
	class LobbyConfig
	{
	public:
		LobbyConfig();

		int GetPlayersNumber() const noexcept;
		int GetDrawTime() const noexcept;
		int GetRoundsNumber() const noexcept;

	private:
		const std::string kConfigFile{ "LobbyConfig.txt" };

	private:
		int m_playersNumber = 2;
		int m_drawTime = 60;
		int m_roundsNumber = 4;
	};
}