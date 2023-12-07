#pragma once

#include <string>

namespace http
{
	class GameSettings
	{
	public:
		GameSettings();

		~GameSettings() = default;

	private:
		const std::string kSettingsFile{ "GameSettings.txt" };
	
	private:
		float m_drawTime;
		int m_roundsNumber;
		bool m_customRounds;
		int m_customRoundChance;
	};
}

