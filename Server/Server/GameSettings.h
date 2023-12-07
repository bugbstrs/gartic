#pragma once

#include <string>
#include <fstream>

namespace http
{
	class GameSettings
	{
	public:
		GameSettings();

		~GameSettings() = default;

		bool GetCustomRounds() const noexcept;
		int GetRoundsNumber() const noexcept;
		int GetCustomRoundChance() const noexcept;
		int GetPlayersNumber() const noexcept;
		float GetDrawTime() const noexcept;

	private:
		const std::string kSettingsFile{ "GameSettings.txt" };
	
	private:
		bool m_customRounds;
		
		int m_roundsNumber;
		int m_customRoundChance;
		int m_playersNumber;

		float m_drawTime;
	};
}

