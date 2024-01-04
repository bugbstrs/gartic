#pragma once

#include <string>
#include <fstream>

namespace http
{
	class GameSettings
	{
	public:
		GameSettings();

		int GetRoundsNumber() const noexcept;
		int GetPlayersNumber() const noexcept;
		int GetDrawTime() const noexcept;
		int GetWordCount() const noexcept;

		void SetWordCount(int wordCount) noexcept;
		void SetRoundsNumber(int roundsNumber) noexcept;
		void SetDrawTime(int drawTime) noexcept;

	private:
		const std::string kSettingsFile{ "GameSettings.txt" };
	
	private:
		int m_roundsNumber;
		int m_playersNumber;
		int m_wordCount;

		int m_drawTime;
	};
}

